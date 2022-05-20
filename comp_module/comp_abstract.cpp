#include "comp_abstract.h"
#include "../canvas.h"

namespace LewzenServer {    
    //////////////////
    //// 接口
    //////////////////
    //// 基本
    // 构造
    ComponentAbstract::ComponentAbstract () {
        _id = uuid::generate_uuid_v4();
    }
    // 获取Id
    const std::string ComponentAbstract::getId() const {
        return _id;
    }
    //// 描述信息
    // 添加模块类型
    void ComponentAbstract::addModuleTypes(const std::string &module) {
        _modules.insert(module);
    }
    // 设置组件类型
    void ComponentAbstract::setType(const std::string &type) {
        _type = type;
    }
    // 获取模块类型
    const std::set<std::string> ComponentAbstract::getModuleTypes() const {
        return _modules;
    }
    // 查看模块类型是否存在
    bool ComponentAbstract::moduleContains(const std::string &module) const {
        return _modules.count(module);
    }
    // 获取组件类型
    const std::string ComponentAbstract::getType() const {
        return _type;
    }
    //// 树形结构
    // 获取子节点
    std::vector<std::shared_ptr<ComponentAbstract>> ComponentAbstract::getChildren() const {
        std::vector<std::shared_ptr<ComponentAbstract>> vec;
        for (auto &p : children) vec.push_back(p);
        return std::move(vec);
    }
    // 获取父节点
    std::shared_ptr<ComponentAbstract> ComponentAbstract::getParent() const {
        return parent.lock();
    }
    // 获取所有祖先
    std::vector<std::shared_ptr<ComponentAbstract>> ComponentAbstract::getAncestors() const {
        if (auto pp = parent.lock()) {
            auto list = pp->getAncestors();
            list.push_back(pp);
            return std::move(list);
        }
        return std::move(std::vector<std::shared_ptr<ComponentAbstract>>());
    }
    // 获取所有后代
    std::vector<std::shared_ptr<ComponentAbstract>> ComponentAbstract::getDescendants() const {
        auto vec = getChildren();
        for (auto &p : children) {
            auto vecp = p->getAncestors();
            vec.insert(vec.end(), vecp.begin(), vecp.end());
        }
        return std::move(vec);
    }
    // 是祖先（包括自己）
    bool ComponentAbstract::isAncestorOf(const std::weak_ptr<ComponentAbstract> &component) const {
        auto comp = component.lock();
        while (comp) {
            if (comp == shared_from_this()) return true;
            comp = comp->getParent();
        }
        return false;
    }
    // 获取顶级节点
    std::vector<std::shared_ptr<ComponentAbstract>> ComponentAbstract::extractTop(const std::vector<std::shared_ptr<ComponentAbstract>> &components) {
        std::set<int> not_top;
        int n = components.size();
        for (int i = 0; i < n; i++) {
            if (not_top.count(i)) continue;
            for (int j = i + 1; j < n; j++) {
                if (not_top.count(j)) continue;
                auto &a = components[i];
                auto &b = components[j];
                if (a->isAncestorOf(b)) not_top.insert(j); // a是b的祖先，b不是顶级节点
                else if (b->isAncestorOf(a)) not_top.insert(i); // b是a的祖先，a不是顶级节点
            }
        }
        std::vector<std::shared_ptr<ComponentAbstract>> vec;
        for (int i = 0; i < n; i++) if (!not_top.count(i)) vec.push_back(components[i]);
        return std::move(vec);
    }
    // 增加子节点
    void ComponentAbstract::addChild(const std::weak_ptr<ComponentAbstract> &child) {
        auto c = child.lock(); if (!c) return;
        if (children.count(c)) return; // 已经是孩子
        auto cp = c->parent; children.insert(c); // this增加孩子child
        if (auto p = cp.lock()) p->removeChild(c); // child的父亲移除child
        c->parent = shared_from_this(); // 令child的父亲为this
        c->onParentChanged(std::shared_ptr<ComponentAbstract>(nullptr), shared_from_this()); // 父亲变更事件
        onChildAdded(child); // 孩子增加事件
    }
    // 移除子节点
    void ComponentAbstract::removeChild(const std::weak_ptr<ComponentAbstract> &child) {
        auto c = child.lock(); if (!c) return;
        if (!children.count(c)) return; // 不是孩子
        children.erase(c); // this移除孩子child
        c->parent = std::shared_ptr<ComponentAbstract>(nullptr); // 令child的父亲为null
        c->onParentChanged(shared_from_this(), std::shared_ptr<ComponentAbstract>(nullptr)); // 父亲变更事件
        onChildRemoved(child); // 孩子移除事件
    }
    //// 实用方法
    // 创建该坐标系下的点
    Lewzen::Point2D ComponentAbstract::createPoint() const {
        return Lewzen::Point2D(0, 0, getCoordinateSystem());
    }
    Lewzen::Point2D ComponentAbstract::createPoint(const double &x, const double &y) const {
        return Lewzen::Point2D(x, y, getCoordinateSystem());
    }
    // 创建一个关键点
    std::shared_ptr<CorePoint> ComponentAbstract::createCorePoint(const std::string &id) const {
        return std::make_shared<CorePoint>(id, getCoordinateSystem());
    }
    std::shared_ptr<CorePoint> ComponentAbstract::createCorePoint(const std::string &id, const double &x, const double &y) const {
        auto p = std::make_shared<CorePoint>(id, x, y, getCoordinateSystem());
        return p;
    }

    // 反序列化生成
    std::shared_ptr<ComponentAbstract> ComponentAbstract::deserialize(const json &j) {
        auto de = Canvas::add((std::string)j["type"]);
        *de = j; // 反序列化
        return de;
    }
}