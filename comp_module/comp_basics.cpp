#include "comp_basics.h"
#include "../canvas.h"

namespace LewzenServer {
    //////////////////
    //// 接口
    //////////////////
    //// 注册
    bool ComponentBasics::registered = false;
    // 注册接口
    void ComponentBasics::registering() {
        registered = true;
        Register::addEvent("get_modules", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                param["modules"] = comp->getModuleTypes();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                std::set<std::string> typec, types; bool not_set = true;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                    if (not_set) typec = comp->getModuleTypes();
                    else std::set_intersection(comp->getModuleTypes().begin(), comp->getModuleTypes().end(), types.begin(), types.end(),
                                        std::inserter(typec, typec.begin())); // 求交集
                    types = typec; not_set = false;
                }
                param["modules"] = types;
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_points", [&](json &param) {
            std::vector<std::weak_ptr<LewzenServer::CorePoint>> points;
            // 将关键点集合转为json对象(画布坐标系)
            std::function<const std::vector<json>(const std::string &)> points_to_str = [&](const std::string &comp_id) {
                std::vector<json> vec;
                for (auto &p : points) {
                    if (auto pp = p.lock()) {
                        auto cp = *pp; json j; j["comp_id"] = comp_id;
                        cp.serialize(j);
                        auto pc = cp(Lewzen::CanvasCoordinateSystem::canvas_coordinate_system);
                        j["x"] = pc.get_x();
                        j["y"] = pc.get_y();
                        vec.push_back(j);
                    }
                }
                return std::move(vec);
            };
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                points = comp->getCorePoints();
                param["points"] = points_to_str(comp->getId());
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                std::vector<json> vec;
                for (int i = 0; i < cursors.size(); i++) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursors[i]); // 动态类型转换
                    points = comp->getCorePoints();
                    auto vecc = points_to_str(comp->getId());
                    vec.insert(vec.end(), vecc.begin(), vecc.end());
                }
                param["points"] = vec;
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_children", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &comp){
                std::vector<std::weak_ptr<ComponentAbstract>> vec;
                for (auto &c : comp->getChildren()) vec.push_back(c);
                Register::listComponentId(param["ids"], vec);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &comps){
                std::set<std::shared_ptr<ComponentAbstract>> unn;
                for (auto comp : comps) {
                    for (auto &c : comp->getChildren()) if (c) unn.insert(c);
                }
                Register::listComponentId(param["ids"], unn);
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_parent", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &comp){
                std::vector<std::weak_ptr<ComponentAbstract>> vec;
                vec.push_back(comp->getParent());
                Register::listComponentId(param["ids"], vec);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &comps){
                std::set<std::shared_ptr<ComponentAbstract>> unn;
                for (auto comp : comps) if (auto p = comp->getParent()) unn.insert(p);
                Register::listComponentId(param["ids"], unn);
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_ancestors", [&](json &param) {
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &comp){
                std::vector<std::weak_ptr<ComponentAbstract>> vec;
                for (auto &c : comp->getAncestors()) vec.push_back(c);
                Register::listComponentId(param["ids"], vec);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &comps){
                std::set<std::shared_ptr<ComponentAbstract>> unn;
                for (auto comp : comps) {
                    for (auto &c : comp->getAncestors()) if (c) unn.insert(c);
                }
                Register::listComponentId(param["ids"], unn);
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("link", [&](json &param) {
            std::string id1 = param["id1"], id2 = param["id2"];
            if (Canvas::components.count(id1) && Canvas::components.count(id2)) {
                if (Canvas::components[id1]->isAncestorOf(Canvas::components[id2])) {
                    param["status"] = ILLEGAL;
                } else {
                    Canvas::components[id2]->addChild(Canvas::components[id1]);
                    param["status"] = SUCCEED;
                }
            } else param["status"] = NULLPTR;
            return param;
        });
        Register::addEvent("unlink", [&](json &param) {
            std::string id1 = param["id1"], id2 = param["id2"];
            if (Canvas::components.count(id1) && Canvas::components.count(id2)) {
                Canvas::components[id2]->removeChild(Canvas::components[id1]);
                Canvas::components[id1]->removeChild(Canvas::components[id2]);
                param["status"] = SUCCEED;
            } else param["status"] = NULLPTR;
            return param;
        });
        Register::addEvent("get_center", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &comp){
                json li; json jp; auto p = comp->getCenter();
                jp["x"] = p.get_x(), jp["y"] = p.get_y();
                li.push_back(jp);
                param["centers"] = li;
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &comps){
                json li; 
                for (auto comp : comps) {
                    json jp; auto p = comp->getCenter();
                    jp["x"] = p.get_x(), jp["y"] = p.get_y();
                    li.push_back(jp);
                }
                param["centers"] = li;
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("move", [&](json &param) {
            double dx = param["dx"], dy = param["dy"];
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                comp->move(dx, dy);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                std::vector<std::shared_ptr<ComponentBasics>> vec;
                for (auto cursor : cursors) vec.push_back(std::dynamic_pointer_cast<ComponentBasics>(cursor)); // 动态类型转换
                for (auto comp : extractMoveBindTop(vec)) comp->move(dx, dy); // 仅移动顶级移动绑定组件
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("move_point", [&](json &param) {
            double dx = param["dx"], dy = param["dy"];
            std::string id=param["id"], pid = param["pid"];
            if (!Canvas::components.count(id)) {
                param["status"] = NULLPTR;
                return param;
            }
            auto comp = std::dynamic_pointer_cast<ComponentBasics>(Canvas::components[id]); // 动态类型转换
            comp->moveCorePoint(pid, dx, dy);
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("remove_point", [&](json &param) {
            std::string id=param["id"], pid = param["pid"];
            if (!Canvas::components.count(id)) {
                param["status"] = NULLPTR;
                return param;
            }
            auto comp = std::dynamic_pointer_cast<ComponentBasics>(Canvas::components[id]); // 动态类型转换
            if (comp->corePoints[pid]->getCanRemove()) { // 非法操作
                param["status"] = ILLEGAL;
                return param;
            }
            comp->removeCorePoint(pid);
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_move_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                param["status"] = SUCCEED;
                param["move_bind"] = comp->isMoveBinded();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                double binded = 0;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                    if (!matched) binded = comp->isMoveBinded(), matched = true;
                    else if (binded != comp->isMoveBinded()) { // 多值
                        matched = false;
                        break;
                    }
                }
                if (matched) {
                    param["move_bind"] = binded;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("enable_move_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                comp->setMoveBinded(true);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                    comp->setMoveBinded(true);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("disable_move_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                comp->setMoveBinded(false);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                    comp->setMoveBinded(false);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("forward", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                comp->forward();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                    comp->forward();
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("backward", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                comp->backward();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                    comp->backward();
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("front", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                comp->front();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                    comp->front();
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("back", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                comp->back();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentBasics>(cursor); // 动态类型转换
                    comp->back();
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
    }
    // 设置所有关键点
    void ComponentBasics::setCorePoints(const std::vector<std::shared_ptr<CorePoint>> &corePointList) {
        for (auto &p : corePointList) corePoints[p->getId()] = p;
    }

    //// 基本
    // 构造
    ComponentBasics::ComponentBasics() {
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
    }
    //// 持有
    // 获取所有关键点
    std::vector<std::weak_ptr<CorePoint>> ComponentBasics::getCorePoints() const {
        std::vector<std::weak_ptr<CorePoint>> vec;
        for (auto &p : corePoints) vec.push_back(p.second);
        return std::move(vec);
    }
    // 获取维护的SVGI
    std::weak_ptr<Lewzen::SVGIElement> ComponentBasics::getSVGI() const {
        return SVGIG;
    }
    // 获取需要的Defs
    std::vector<std::weak_ptr<Lewzen::SVGIElement>> ComponentBasics::getDefs() const {
        return Defs;
    }
    // 获取图形中心
    Lewzen::Point2D ComponentBasics::getCenter() const {
        if (corePoints.size() == 0) return createPoint(0, 0);
        std::vector<std::shared_ptr<Lewzen::Point2D>> points;
        for (auto &p : corePoints) points.push_back(p.second);
        return Lewzen::geometry_centroid(points);
    }
    // 获取坐标系
    const std::shared_ptr<Lewzen::CoordinateSystem> ComponentBasics::getCoordinateSystem() const {
        return Lewzen::CanvasCoordinateSystem::canvas_coordinate_system;
    }
    // 非构造初始化
    void ComponentBasics::init() {
        for (auto &c : getChildren()) c->init(); // 初始化子组件
        SVGIG = std::make_shared<Lewzen::SVGIG>();
        SVGIG->Id = getId();
        SVGIG->Id.commit();
    }
    // 拷贝
    ComponentAbstract &ComponentBasics::operator=(const ComponentAbstract &comp) {
        if (comp.getType() != getType()) return *this; // 要求组件类型一致
        auto &p = dynamic_cast<const ComponentBasics &>(comp);
        auto chd = getChildren(); for (auto &c : chd) removeChild(c); // 移除现有链接
        for (auto c : p.getChildren()) addChild(c->clone()); // 复制子节点
        return *this;
    }
    // 克隆
    std::shared_ptr<ComponentAbstract> ComponentBasics::clone() {
        return Canvas::copy(shared_from_this());
    }
    // 序列化，并记录已操作的
    void ComponentBasics::serialize(json &j, std::vector<std::string> &processed) {
        j["modules"] = getModuleTypes();
        j["type"] = getType();
        j["children"] = {};
        processed.push_back(getId());
        for (auto c : getChildren()) { // 序列化子节点
            json jc;
            c->serialize(jc, processed);
            j["children"].push_back(jc);
        }
        j["core_points"] = {};
        for (auto &p : corePoints) { // 关键点列表转json
            j["core_points"][p.first] = {};
            p.second->serialize(j["core_points"][p.first]);
        }
    }
    // 反序列化
    ComponentAbstract &ComponentBasics::operator=(const json &j) {
        if (j["type"] != getType()) return *this; // 要求组件类型一致
        auto &jc = j["core_points"];
        for (auto& [k, v] : jc.items()) { // json转关键点列表
            auto p = createCorePoint(k);
            p->deserialize(v);
            corePoints[k] = p;
        }
        for (auto c : j["children"]) addChild(deserialize(c)); // 复制子节点
        return *this;
    }
    //// 事件
    // 被添加事件
    void ComponentBasics::onAdded() {
        Canvas::updateViewBox(shared_from_this()); // 更新画布大小
        for (auto c : getChildren()) c->onAdded(); // 遍历孩子, 唤起被添加事件
    }
    // 被更新事件
    void ComponentBasics::onChanged() {
        Canvas::addUpdatedComponents(getId()); // 记录被更新
        Canvas::updateViewBox(shared_from_this()); // 更新画布大小
    }
    // 被删除事件
    void ComponentBasics::onRemoved(int time) {
        for (auto c : getChildren()) {
            Canvas::remove(c, time); // 从上下文删除孩子
            c->onRemoved(time); // 调用被删除事件
        }
        Canvas::updateViewBox(shared_from_this()); // 更新画布大小
    }
    // 被重添加事件
    void ComponentBasics::onReadded(int time) {
        Canvas::updateViewBox(shared_from_this()); // 更新画布大小
        for (auto c : getChildren()) { // 向上下文添加孩子, 唤起重添加事件
            Canvas::readd(c); // 重添加孩子
            c->onReadded(time); // 调用重添加事件
        }
    }
    // 被释放事件
    void ComponentBasics::onDiscarded() {
        for (auto c : getChildren()) c->onDiscarded(); // 遍历孩子, 唤起被释放事件
        auto chd = getChildren(); for (auto &c : chd) removeChild(c); // 释放孩子
    }
    // 父亲变更
    void ComponentBasics::onParentChanged(const std::weak_ptr<ComponentAbstract> &prev, const std::weak_ptr<ComponentAbstract> &now) {}
    // 孩子添加
    void ComponentBasics::onChildAdded(const std::weak_ptr<ComponentAbstract> &child) {}
    // 孩子移除
    void ComponentBasics::onChildRemoved(const std::weak_ptr<ComponentAbstract> &child) {}

        
    //// Basics虚接口
    // 移动组件
    void ComponentBasics::move(const double &dx, const double &dy) {
        for (auto &p : getCorePoints()) {
            if (auto pp = p.lock()) {
                *pp += createPoint(dx, dy);
            }
        }
        onMoved(dx, dy); // 移动变换后操作
        onChanged();
    }
    // 移动组件
    void ComponentBasics::moveTo(const double &x, const double &y) {
        auto delta = createPoint(x, y) - getCenter(); // 计算坐标系的Δ
        ComponentBasics::move(delta.get_x(), delta.get_y());
    }
    // 移动关键点
    void ComponentBasics::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        onChanged();
    }
    // 删除关键点
    void ComponentBasics::removeCorePoint(const std::string &id) {
        if (!corePoints.count(id)) return;
        corePoints[id]->on_remove();
        onChanged();
    }
    // 调整层级
    void ComponentBasics::forward() {
        Canvas::forward(getId());
    }
    void ComponentBasics::backward() {
        Canvas::backward(getId());
    }
    void ComponentBasics::front() {
        Canvas::front(getId());
    }
    void ComponentBasics::back() {
        Canvas::back(getId());
    }
    // 移动变换后操作
    void ComponentBasics::onMoved(const double &dx, const double &dy) {
        moveBindEvent(dx, dy);
    }
    // 移动绑定
    bool ComponentBasics::isMoveBinded() const {
        return moveBinded;
    }
    void ComponentBasics::setMoveBinded(bool binded) {
        moveBinded = binded;
    }
    // 获取父移动绑定组件
    std::shared_ptr<ComponentBasics> ComponentBasics::getMoveBindParent() const {
        if (isMoveBinded() && getParent() && getParent()->moduleContains("Basics")) {
            return std::dynamic_pointer_cast<ComponentBasics>(getParent());
        }
        return std::shared_ptr<ComponentBasics>(nullptr);
    }
    // 获取祖先移动绑定组件; 不包括自己
    std::vector<std::shared_ptr<ComponentBasics>> ComponentBasics::getMoveBindAncestors() const {
        std::vector<std::shared_ptr<ComponentBasics>> vec;
        auto comp = std::dynamic_pointer_cast<const ComponentBasics>(shared_from_this());
        while (auto p = comp->getParent()) {
            if (!comp->isMoveBinded() || !p->moduleContains("Basics")) break;
            vec.push_back(std::dynamic_pointer_cast<ComponentBasics>(p));
        }
        return std::move(vec);
    }
    // 是祖先移动绑定组件 (包括自己)
    bool ComponentBasics::isMoveBindAncestorOf(const std::weak_ptr<ComponentBasics> &component) const {
        auto comp = component.lock();
        while (comp) {
            if (comp == shared_from_this()) return true;
            comp = comp->getMoveBindParent();
        }
        return false;
    }
    // 获取移动绑定顶级节点
    std::vector<std::shared_ptr<ComponentBasics>> ComponentBasics::extractMoveBindTop(const std::vector<std::shared_ptr<ComponentBasics>> &components) {
        std::set<int> not_top;
        int n = components.size();
        for (int i = 0; i < n; i++) {
            if (not_top.count(i)) continue;
            for (int j = i + 1; j < n; j++) {
                if (not_top.count(j)) continue;
                auto &a = components[i];
                auto &b = components[j];
                if (a->isMoveBindAncestorOf(b)) not_top.insert(j); // a是b的祖先，b不是顶级节点
                else if (b->isMoveBindAncestorOf(a)) not_top.insert(i); // b是a的祖先，a不是顶级节点
            }
        }
        std::vector<std::shared_ptr<ComponentBasics>> vec;
        for (int i = 0; i < n; i++) if (!not_top.count(i)) vec.push_back(components[i]);
        return std::move(vec);
    }
    // 移动绑定事件
    void ComponentBasics::moveBindEvent(const double &dx, const double &dy) {
        for (auto c : getChildren()) if (c->moduleContains("Basics")) { // 绑定移动，遍历合法孩子进行移动
            auto cb = std::dynamic_pointer_cast<ComponentBasics>(c);
            if (cb->isMoveBinded()) cb->move(dx, dy);
        }
    }
}