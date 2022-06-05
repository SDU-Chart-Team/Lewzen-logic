#include "canvas.h"

namespace LewzenServer {
    std::shared_ptr<Lewzen::SVGISvg> Canvas::svg = std::shared_ptr<Lewzen::SVGISvg>(nullptr); // <svg>
    std::shared_ptr<Lewzen::SVGIDefs> Canvas::defs = std::shared_ptr<Lewzen::SVGIDefs>(nullptr); // <defs>
    std::unordered_map<Lewzen::HASH_CODE, int> Canvas::defs_counter = {}; // defs计数器
    std::shared_ptr<Lewzen::SVGIG> Canvas::els = std::shared_ptr<Lewzen::SVGIG>(nullptr); // <g>
    std::unordered_map<std::string, std::shared_ptr<ComponentAbstract>> Canvas::components = {}; // 当前组件集合
    std::multimap<int, std::shared_ptr<ComponentAbstract>> Canvas::removed = {}; // 暂存区
    std::unordered_map<Lewzen::HASH_CODE, int> Canvas::removed_layer; // 暂存区组件层级
    std::vector<std::string> Canvas::added_comp_ids = {}; // 被添加的组件id
    std::set<std::string> Canvas::updated_comp_ids = {}; // 被更新的组件id
    std::vector<std::string> Canvas::removed_comp_ids = {}; // 被移出的组件id
    std::vector<std::shared_ptr<ComponentAbstract>> Canvas::toreadd_comps = {}; // 将要重添加的组件id
    std::unordered_map<std::string, int> Canvas::readded_layer_map = {}; // 重添加组件的层级
    std::vector<std::pair<std::string, std::string>> Canvas::copied_comp_pairs = {}; // 复制组件对
    std::unordered_map<std::string, int> Canvas::layer_map = {}; // 层级映射
    std::unordered_map<std::string, int> Canvas::last_layer_map = {}; // 上次层级映射

    const std::string Canvas::init() {
        // DOM树
        svg = std::make_shared<Lewzen::SVGISvg>();
        defs = std::make_shared<Lewzen::SVGIDefs>(); defs->Id = "defs";
        auto last = std::make_shared<Lewzen::SVGIG>(); last->Id = "last_map";
        auto text = std::make_shared<Lewzen::SVGIG>(); text->Id = "text_map";
        els = std::make_shared<Lewzen::SVGIG>(); els->Id = "shape_map";
        auto hover = std::make_shared<Lewzen::SVGIG>(); hover->Id = "hover_map";
        auto key = std::make_shared<Lewzen::SVGIG>(); key->Id = "key_map";
        svg->add(defs);
        svg->add(last);
        svg->add(text);
        svg->add(els);
        svg->add(hover);
        svg->add(key);

        // ViewBox
        width = A4WIDTH, height = A4HEIGHT;
        svg->ViewBox.bind([&](){ return std::vector<int>{ x, y, width, height }; });

        // 返回outerHTML
        svg->commit();
        return svg->outer_SVG();
    }

    const std::string Canvas::HTML() {
        els->commit_this();
        return svg->outer_SVG();
    }
    
    //// 用于注册器
    void Canvas::_component_added(const std::shared_ptr<ComponentAbstract> &comp) {
        components[comp->getId()] = comp; // 将组件加入当前组件集合
        if (auto el = comp->getSVGI().lock()) { // 将组件维护的SVGI加入DOM树
            els->add(el); // 加入到末尾
        }
        for (auto &_def : comp->getDefs()) { // 维护Defs表
            if (auto def = _def.lock()) {
                Lewzen::HASH_CODE hash = def->hash();
                if (!defs_counter.count(hash)) defs->add(def);
                defs_counter[hash]++;
            }
        }
        updateLayerMap(); // 更新层级映射
    }
    void Canvas::_component_removed(const std::shared_ptr<ComponentAbstract> &comp) {
        components.erase(comp->getId()); // 将组件从当前组件集合移除
        if (auto el = comp->getSVGI().lock()) { // 将组件维护的SVGI从DOM树移除
            removed_layer[el->hash()] = getLayer(comp->getId()); // 记录层级
            els->remove(el); // 移除
        }
        for (auto &_def : comp->getDefs()) { // 维护Defs表
            if (auto def = _def.lock()) {
                Lewzen::HASH_CODE hash = def->hash();
                if (defs_counter.count(hash)) defs_counter[hash]--;
                if (defs_counter[hash] == 0) defs_counter.erase(hash);
            }
        }
        updateLayerMap(); // 更新层级映射
    }
    // 增加组件
    // 将组件添加进上下文
    void Canvas::add(std::weak_ptr<ComponentAbstract> comp) {
        if (auto c = comp.lock()) {
            added_comp_ids.push_back(c->getId());
            _component_added(c); // 加入组件
        }
    }
    // 创建组件
    std::shared_ptr<ComponentAbstract> Canvas::add(const std::string &type) {
        auto comp = ComponentFactory::createComponent(type); // 创建一个组件
        comp->init(); // 初始化组件
        add(comp);
        comp->onAdded(); // 添加事件
        return comp;
    }
    // 指向组件
    std::weak_ptr<ComponentAbstract> Canvas::cursor(const std::string &id) {
        if (!components.count(id)) return std::shared_ptr<ComponentAbstract>(nullptr);
        return components[id];
    }
    // 指向多个组件
    std::vector<std::weak_ptr<ComponentAbstract>> Canvas::cursors(const std::vector<std::string> &ids) {
        auto vec = std::vector<std::weak_ptr<ComponentAbstract>>();
        for (auto &id : ids) if (components.count(id)) vec.push_back(components[id]);
        return std::move(vec);
    }
    // 暂时移除组件
    // 将组件从上下文移出
    void Canvas::remove(std::weak_ptr<ComponentAbstract> comp, const int &time) {
        if (auto c = comp.lock()) {
            removed_comp_ids.push_back(c->getId());
            readded_layer_map[c->getId()] = getLayer(c->getId()); // 记录层级
            removed.insert({time, c}); // 将组件移动到暂存区
        }
    }
    // 移除选中的组件
    void Canvas::remove(const int &time) {
        json j;
        Register::switchBoth(j, "", // 跳过注册检查
        [&](std::shared_ptr<ComponentAbstract> &comp){
            remove(comp, time);
            if (comp->getParent()) comp->getParent()->removeChild(comp); // 移除父子关系
            comp->onRemoved(time); // 移除事件
        },
        [&](std::vector<std::shared_ptr<ComponentAbstract>> &comps){
            for (auto comp : ComponentAbstract::extractTop(comps)) {
                remove(comp, time);
                if (comp->getParent()) comp->getParent()->removeChild(comp); // 移除父子关系
                comp->onRemoved(time); // 移除事件
            }
        });
        for (auto &id : removed_comp_ids) {
            if (components.count(id)) _component_removed(components[id]); // 移除组件
        }
    }
    // 复制组件
    // 用组件复制组件
    std::shared_ptr<ComponentAbstract> Canvas::copy(std::weak_ptr<ComponentAbstract> comp) {
        if (auto c = comp.lock()) {
            auto copied = Canvas::add(c->getType());
            copied_comp_pairs.push_back({copied->getId(), c->getId()}); // 记录拷贝关系
            *copied = *c; // 拷贝
            return copied;
        }
        return std::shared_ptr<ComponentAbstract>(nullptr);
    }
    // 复制选中组件
    void Canvas::copy() {
        json j;
        Register::switchBoth(j, "", // 跳过注册检查
        [&](std::shared_ptr<ComponentAbstract> &comp){
            auto comp_c = comp->clone(); // 拷贝组件
        },
        [&](std::vector<std::shared_ptr<ComponentAbstract>> &comps){
            for (auto comp : ComponentAbstract::extractTop(comps)) {
                auto comp_c = comp->clone(); // 拷贝组件
            }
        });
        // 重排组件使得层级正确
        std::map<int, std::string> idx_map;
        for (auto &p : copied_comp_pairs) if (components.count(p.first) && components.count(p.second)) idx_map[getLayer(p.second)] = p.first;
        for (auto &p : idx_map) setLayer(p.second, -1); // 移至最后

        copied_comp_pairs.clear();
    }
    // 重新增加组件
    // 重添加一个组件
    void Canvas::readd(std::weak_ptr<ComponentAbstract> comp) {
        if (auto c = comp.lock()) {
            toreadd_comps.push_back(c);
        }
    }
    // 重添加所有最后时刻的所有组件
    void Canvas::readd() {
        if (removed.size() == 0) return;
        int time = removed.rbegin()->first; // 获取时机
        auto bound = removed.lower_bound(time);
        std::vector<std::shared_ptr<ComponentAbstract>> comps;
        for (auto it = removed.rbegin(); it->first >= bound->first && it != removed.rend(); it++) comps.push_back(it->second); // 取出组件
        for (auto &comp: ComponentBasics::extractTop(comps)) {
            readd(comp); // 重添加
            comp->onReadded(time); // 重添加事件
            if (comp->getParent()) comp->getParent()->addChild(comp); // 添加父子关系
        }
        removed.erase(bound, removed.end());

        // 进行重添加，改变层级
        std::map<int, std::string> seq;
        for (auto &comp : toreadd_comps) {
            Canvas::add(comp);  // 添加进上下文
            if (readded_layer_map.count(comp->getId())) seq[readded_layer_map[comp->getId()]] = comp->getId();
            readded_layer_map.erase(comp->getId());
            updateViewBox(comp);
        }
        for (auto &mp : seq) setLayer(mp.second, mp.first);
        toreadd_comps.clear();
    }
    // 丢弃组件
    bool Canvas::discard(const int &time) {
        auto bound = removed.lower_bound(time);
        for (auto it = removed.rbegin(); it->first >= bound->first && it != removed.rend(); it++) {
            readded_layer_map.erase(it->second->getId()); // 删除记录的层级
            it->second->onDiscarded(); // 丢弃事件
        }
        removed.erase(bound, removed.end());
        return true;
    }
    // 序列化
    const json Canvas::serialize() {
        std::vector<std::shared_ptr<ComponentAbstract>> comps;
        std::vector<std::string> processed;
        for (auto p : components) comps.push_back(p.second);
        comps = ComponentAbstract::extractTop(comps);
        json jl;
        for (auto comp : comps) {
            json jc;
            comp->serialize(jc, processed);
            jl.push_back(jc);
        }
        json idxs;
        for (auto &id : processed) { // 记录层级
            idxs.push_back(getLayer(id));
        }
        json j;
        j["indices"] = idxs;
        j["comps"] = jl;
        return j;
    }
    // 反序列化
    void Canvas::deserialize(const json &j) {
        std::vector<std::string> processed;
        for (auto &jc : j["comps"]) {
            ComponentAbstract::deserialize(jc);
        }
        std::vector<int> idxs = j["indices"]; // 记录层级
        std::vector<std::shared_ptr<Lewzen::SVGIElement>> n_els = std::vector<std::shared_ptr<Lewzen::SVGIElement>>(idxs.size());
        auto o_els = els->children();
        for (int i = 0; i < idxs.size(); i++) n_els[idxs[i]] = o_els[i];
        els->children(n_els);
        updateLayerMap(); // 更新层级映射
    }

    // 添加被更新的组件
    void Canvas::addUpdatedComponents(const std::string &id) {
        updated_comp_ids.insert(id);
    }
    // 获取被添加的组件信息
    void Canvas::getAddedComponents(std::vector<std::string> &ids, std::vector<std::string> &tops) {
        std::vector<std::shared_ptr<ComponentAbstract>> comps;
        for (auto &id : added_comp_ids) if (components.count(id)) comps.push_back(components[id]);
        for (auto &top : ComponentBasics::extractTop(comps)) tops.push_back(top->getId()); // 获取顶级组件id表

        std::map<int, std::string> idx_map;
        for (auto &id : added_comp_ids) if (components.count(id)) idx_map[getLayer(id)] = id;
        for (auto &p : idx_map) ids.push_back(p.second); // 获取按层级排序的组件id表
    }
    // 获取被移除的组件信息
    void Canvas::getRemovedComponents(std::vector<std::string> &ids) {
        ids = removed_comp_ids;
    }
    
    //// 用于层级变化
    void Canvas::updateLayerMap() {
        layer_map.clear();
        for (int i = 0; i < els->children().size(); i++) {
            layer_map[els->child(i)->Id.get()] = i;
        }
    }
    int Canvas::getLayer(const std::string &id) {
        if (layer_map.count(id)) return layer_map[id];
        return -1;
    }
    bool Canvas::setLayer(const std::string &id, int layer) {
        int idx = getLayer(id);
        if (idx == -1) return false;
        if (layer >= els->children().size() - 1) layer = -1;
        if (auto el = components[id]->getSVGI().lock()) {
            els->remove(el); // 首先移除
            els->add(el, layer);// 再加入到指定位置
        }
        updateLayerMap(); // 更新层级映射
        return true;
    }
    // 向前
    bool Canvas::forward(const std::string &id) {
        if (!components.count(id)) return false;
        int idx = getLayer(id);
        if (idx == -1) return false;
        if (idx == els->children().size() - 1) return true; // 已经是最前
        setLayer(id, idx + 1); //向前
        return true;
    }
    // 向后
    bool Canvas::backward(const std::string &id) {
        if (!components.count(id)) return false;
        int idx = getLayer(id);
        if (idx == -1) return false;
        if (idx == 0) return true; // 已经是最后
        setLayer(id, idx - 1); //向后
        return true;
    }
    // 最前
    bool Canvas::front(const std::string &id) {
        if (!components.count(id)) return false;
        int idx = getLayer(id);
        if (idx == -1) return false;
        setLayer(id, -1); //最前
        return true;
    }
    // 最后
    bool Canvas::back(const std::string &id) {
        if (!components.count(id)) return false;
        int idx = getLayer(id);
        if (idx == 0) return false;
        setLayer(id, 0); //最后
        return true;
    }
    
    //// 用于画布变化
    int Canvas::x = 0, Canvas::y = 0, Canvas::width = 0, Canvas::height = 0;
    Canvas::CPHeap Canvas::infX = CPHeap("<");
    Canvas::CPHeap Canvas::infY = CPHeap("<");
    Canvas::CPHeap Canvas::supX = CPHeap(">");
    Canvas::CPHeap Canvas::supY = CPHeap(">");
    const int Canvas::A4WIDTH = 1629, Canvas::A4HEIGHT = 2209;
    void Canvas::updateViewBoxFromComponent(std::weak_ptr<ComponentAbstract> component) {
        auto comp = component.lock();
        if (!comp) return;
        bool is_updating = components.count(comp->getId());

        for (auto &p : comp->getCorePoints()) { // 更新点集
            if (auto pp = p.lock()) {
                auto cpid = comp->getId() + ":" + pp->getId();
                infX.remove(cpid), infY.remove(cpid), supX.remove(cpid), supY.remove(cpid); // 移除旧的
                if (is_updating) { // 增加新的
                    auto canvas_point = (*pp)(Lewzen::CanvasCoordinateSystem::canvas_coordinate_system);
                    infX.add(cpid, canvas_point.get_x()), infY.add(cpid, canvas_point.get_y());
                    supX.add(cpid, canvas_point.get_x()), supY.add(cpid, canvas_point.get_y());
                }
            }
        }
    }
    void Canvas::setCanvasTranslate() {
        // 获取上下界
        int lowerX = std::floor(infX.top()), upperX = std::ceil(supX.top());
        int lowerY = std::floor(infY.top()), upperY = std::ceil(supY.top());
        lowerX = lowerX-((lowerX%A4WIDTH)+A4WIDTH)%A4WIDTH;
        upperX = upperX+(A4WIDTH-(upperX%A4WIDTH))%A4WIDTH;
        lowerY = lowerY-((lowerY%A4HEIGHT)+A4HEIGHT)%A4HEIGHT;
        upperY = upperY+(A4HEIGHT-(upperY%A4HEIGHT))%A4HEIGHT;
        
        // 更新viewBox
        x = lowerX, y = lowerY;
        width = std::max(upperX - lowerX, A4WIDTH), height = std::max(upperY - lowerY, A4HEIGHT);
    }
    // 更新画布大小
    void Canvas::updateViewBox(const std::weak_ptr<ComponentAbstract> &component) {
        updateViewBoxFromComponent(component);
    }

    //// 用于提交
    // 提交DOM Commands; 返回DOM Commands
    const std::string Canvas::commit() {
        std::stringstream ss;
        setCanvasTranslate(); // 更新ViewBox

        //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        // 处理子元素
        if (removed_comp_ids.size() > 0 || added_comp_ids.size() > 0 || updated_comp_ids.size() > 0) {
            ss << "child 3" << std::endl;
            std::set<std::string> unupdated_comp_ids; for (auto &mp : last_layer_map) unupdated_comp_ids.insert(mp.first);
            // 提取索引
            std::vector<int> removal; for (auto &id : removed_comp_ids) removal.push_back(last_layer_map[id]), updated_comp_ids.erase(id), unupdated_comp_ids.erase(id);
            std::vector<int> addition; for (auto &id : added_comp_ids) addition.push_back(layer_map[id]), updated_comp_ids.erase(id);
            std::vector<std::pair<int, int>> changed; for (auto &id : updated_comp_ids) changed.push_back({layer_map[id], last_layer_map[id]}), unupdated_comp_ids.erase(id);
            std::vector<std::pair<int, int>> unchanged; for (auto &id : unupdated_comp_ids) unchanged.push_back({layer_map[id], last_layer_map[id]});
            // 处理删除的元素
            // remove
            int m = layer_map.size(), n = last_layer_map.size();
            int *indices = new int[m], *_removed = new int[n];
            std::fill(indices, indices + m, 0); std::fill(_removed, _removed + n, 0);
            for (auto &r : removal) _removed[r] = 1;
            for (int i = 1; i < n; i++) _removed[i] += _removed[i - 1];
            for (auto &r : removal) ss << "remove " << r - (r > 0 ? _removed[r - 1] : 0) << std::endl;
            // append
            for (auto &a : addition) {
                els->child(a)->commit();
                auto svg = els->child(a)->outer_SVG();
                ss << "append " << svg.size() << std::endl << svg << std::endl;
            }
            // change
            for (auto &c : changed) {
                auto &a = c.first; auto &b = c.second;
                auto &s = els->child(a)->commit();
                if (s == Lewzen::STR_NULL) continue;
                ss << "child " << b - _removed[b] << std::endl;
                ss << s;
                ss << "parent" << std::endl;
            }
            // sort
            for (auto &c : unchanged) {
                auto &a = c.first; auto &b = c.second;
                indices[b - _removed[b]] = a;
            }
            for (auto &c : changed) {
                auto &a = c.first; auto &b = c.second;
                indices[b - _removed[b]] = a;
            }
            for (int i = 0; i < addition.size(); i++) {
                auto &a = addition[i];
                indices[unchanged.size() + changed.size() + i] = a;
            }
            bool ordered = true;
            for (int i = 0; i < m && ordered; i++) if (indices[i] != i) ordered = false;
            if (!ordered) {
                ss << "sort \"";
                for (int i = 0; i < m; i++) {
                    ss << indices[i];
                    if (i < m - 1) ss << ",";
                }
                ss << "\"" << std::endl;
            }
            delete[] _removed; delete[] indices;

            // 应用层级更新
            added_comp_ids.clear();
            removed_comp_ids.clear();
            updated_comp_ids.clear();
            last_layer_map = layer_map;
        
            ss << "parent" << std::endl;
        }
        //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        //std::cout << "timer = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;

        ss << "child 0" << std::endl;
        ss << defs->commit() << std::endl; // 更新预定义域
        ss << "parent" << std::endl;
        
        ss << svg->commit_this() << std::endl; // 更新画布
        return ss.str();
    }
}
