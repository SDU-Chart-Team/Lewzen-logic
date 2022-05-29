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
    std::vector<std::string> Canvas::removed_comp_ids = {}; // 被移出的组件id
    std::unordered_map<std::string, int> Canvas::readded_layer_map = {}; // 重添加组件的层级
    std::vector<std::pair<std::string, std::string>> Canvas::copied_comp_pairs = {}; // 复制组件对

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
        return svg->outer_SVG();
    }
    
    //// 用于注册器
    void Canvas::_component_added(const std::shared_ptr<ComponentAbstract> &comp) {
        components[comp->getId()] = comp; // 将组件加入当前组件集合
        added_comp_ids.push_back(comp->getId());
        if (auto el = comp->getSVGI().lock()) { // 将组件维护的SVGI加入DOM树
            if (removed_layer.count(el->hash())) { // 加入特定层级
                els->add(el, removed_layer[el->hash()]);
                removed_layer.erase(el->hash());
            } else els->add(el); // 加入到末尾
        }
        for (auto &_def : comp->getDefs()) { // 维护Defs表
            if (auto def = _def.lock()) {
                Lewzen::HASH_CODE hash = def->hash();
                if (!defs_counter.count(hash)) defs->add(def);
                defs_counter[hash]++;
            }
        }
    }
    void Canvas::_component_removed(const std::shared_ptr<ComponentAbstract> &comp) {
        components.erase(comp->getId()); // 将组件从当前组件集合移除
        removed_comp_ids.push_back(comp->getId());
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
    }
    // 增加组件
    // 将组件添加进上下文
    void Canvas::add(std::weak_ptr<ComponentAbstract> comp) {
        if (auto c = comp.lock()) {
            c->init(); // 初始化组件
            _component_added(c); // 加入组件
        }
    }
    // 创建组件
    std::shared_ptr<ComponentAbstract> Canvas::add(const std::string &type) {
        auto comp = ComponentFactory::createComponent(type); // 创建一个组件
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
            readded_layer_map[c->getId()] = getLayer(c->getId()); // 记录层级
            _component_removed(c); // 移除组件
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
            Canvas::add(c);  // 添加进上下文
            if (readded_layer_map.count(c->getId())) {
                setLayer(c->getId(), readded_layer_map[c->getId()]); // 回到层级
                readded_layer_map.erase(c->getId());
            }
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
            comp->onReadded(time); // 重添加事件
            if (comp->getParent()) comp->getParent()->addChild(comp); // 添加父子关系
            readd(comp); // 重添加            
        }
        removed.erase(bound, removed.end());
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
    }

    // 获取被添加的组件信息
    void Canvas::getAddedComponents(std::vector<std::string> &ids, std::vector<std::string> &tops) {
        std::vector<std::shared_ptr<ComponentAbstract>> comps;
        for (auto &id : added_comp_ids) if (components.count(id)) comps.push_back(components[id]);
        for (auto &top : ComponentBasics::extractTop(comps)) tops.push_back(top->getId()); // 获取顶级组件id表

        std::map<int, std::string> idx_map;
        for (auto &id : added_comp_ids) if (components.count(id)) idx_map[getLayer(id)] = id;
        for (auto &p : idx_map) ids.push_back(p.second); // 获取按层级排序的组件id表

        added_comp_ids.clear();
    }
    // 获取被移除的组件信息
    void Canvas::getRemovedComponents(std::vector<std::string> &ids) {
        ids = removed_comp_ids;

        removed_comp_ids.clear();
    }
    
    //// 用于层级变化
    int Canvas::getLayer(const std::string &id) {
        for (int i = 0; i < els->children().size(); i++) {
            if (els->child(i)->Id.get() == id) {
                return i;
            }
        }
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
        return true;
    }
    // 向前
    bool Canvas::forward(const std::string &id) {
        if (!components.count(id)) return false;
        int idx = getLayer(id);
        if (idx == -1) return false;
        if (idx == els->children().size() - 1) return true; // 已经是最前
        if (auto el = components[id]->getSVGI().lock()) {
            els->remove(el); // 首先移除
            els->add(el, idx + 1);// 再加入到指定位置
        }
        return true;
    }
    // 向后
    bool Canvas::backward(const std::string &id) {
        if (!components.count(id)) return false;
        int idx = getLayer(id);
        if (idx == -1) return false;
        if (idx == 0) return true; // 已经是最后
        if (auto el = components[id]->getSVGI().lock()) {
            els->remove(el); // 首先移除
            els->add(el, idx - 1);// 再加入到指定位置
        }
        return true;
    }
    // 最前
    bool Canvas::front(const std::string &id) {
        if (!components.count(id)) return false;
        int idx = getLayer(id);
        if (idx == -1) return false;
        if (auto el = components[id]->getSVGI().lock()) {
            els->remove(el); // 首先移除
            els->add(el);// 再加入到末尾
        }
        return true;
    }
    // 最后
    bool Canvas::back(const std::string &id) {
        if (!components.count(id)) return false;
        int idx = getLayer(id);
        if (idx == -1) return false;
        if (auto el = components[id]->getSVGI().lock()) {
            els->remove(el); // 首先移除
            els->add(el, 0);// 再加入到开头
        }
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
        upperX = upperX+(A4WIDTH-(upperX%A4HEIGHT))%A4HEIGHT;
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
        setCanvasTranslate();
        return svg->commit();
    }
}
