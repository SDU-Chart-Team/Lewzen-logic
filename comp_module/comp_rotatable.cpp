#include "comp_rotatable.h"
#include "../canvas.h"
#include <cmath>

namespace LewzenServer {
    bool ComponentRotatable::registered = false;
    // 注册接口
    void ComponentRotatable::registering() {
        registered = true;
        Register::addEvent("get_theta", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                param["status"] = SUCCEED;
                param["theta"] = comp->getTheta();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                double theta = 0;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                    if (!matched) theta = comp->getTheta(), matched = true;
                    else if (theta != comp->getTheta()) { // 多值
                        matched = false;
                        break;
                    }
                }
                if (matched) {
                    param["theta"] = theta;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("set_theta", [&](json &param) {
            double theta = param["theta"];
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                comp->setTheta(theta);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                std::vector<std::shared_ptr<ComponentRotatable>> vec;
                for (auto cursor : cursors) vec.push_back(std::dynamic_pointer_cast<ComponentRotatable>(cursor)); // 动态类型转换
                for (auto comp : extractRotateBindTop(vec)) comp->setTheta(theta); // 仅旋转顶级旋转绑定组件
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_rotate_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                param["status"] = SUCCEED;
                param["rotate_bind"] = comp->isRotateBinded();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                double binded = 0;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                    if (!matched) binded = comp->isRotateBinded(), matched = true;
                    else if (binded != comp->isRotateBinded()) { // 多值
                        matched = false;
                        break;
                    }
                }
                if (matched) {
                    param["rotate_bind"] = binded;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("enable_rotate_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                comp->setRotateBinded(true);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                    comp->setRotateBinded(true);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("disable_rotate_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                comp->setRotateBinded(false);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentRotatable>(cursor); // 动态类型转换
                    comp->setRotateBinded(false);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
    }
    // 父可旋转组件
    std::weak_ptr<Lewzen::ComponentRotatable> ComponentRotatable::get_parent() const {
        return getRotateBindParent();
    }
    // 获取坐标系
    const std::shared_ptr<Lewzen::CoordinateSystem> ComponentRotatable::get_coordinate_system() const {
        return getCoordinateSystem();
    }
    // 将组件向量转为画布向量
    Lewzen::Point2D ComponentRotatable::vectorToCanvas(const Lewzen::Point2D& vector) const {
        return to_canvas(getRotateCenter() + vector) - to_canvas(getRotateCenter());
    }
    // 将画布向量转为组件向量
    Lewzen::Point2D ComponentRotatable::vectorFromCanvas(const Lewzen::Point2D& vector) const {
        return from_canvas(to_canvas(getRotateCenter()) + vector) - getRotateCenter();
    }
    // 将组件坐标转为画布坐标
    Lewzen::Point2D ComponentRotatable::pointToCanvas(const Lewzen::Point2D& point) const {
        return to_canvas(point);
    }
    // 将画布坐标转为组件坐标
    Lewzen::Point2D ComponentRotatable::pointFromCanvas(const Lewzen::Point2D& point) const {
        return from_canvas(point);
    }

    ComponentRotatable::ComponentRotatable() {
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
    }

    //// 通用虚接口
    // 获取坐标系
    const std::shared_ptr<Lewzen::CoordinateSystem> ComponentRotatable::getCoordinateSystem() const {
        return std::make_shared<Lewzen::ComponentCoordinateSystem>(std::dynamic_pointer_cast<const Lewzen::ComponentRotatable>(shared_from_this()));
    }
    // 默认为画布下的旋转中心
    Lewzen::Point2D ComponentRotatable::getCenter() const {
        return pointToCanvas(getRotateCenter());
    }
    // 非构造初始化
    void ComponentRotatable::init() {
        // 父类初始化
        ComponentBasics::init();

        // 初始化
        Lewzen::ComponentRotatable::set_svg_element_interface(SVGIG);
        Lewzen::ComponentRotatable::set_theta(0);
        // 应用旋转中心
        set_rotate_center(getRotateCenter());
    }
    // 拷贝
    ComponentAbstract &ComponentRotatable::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        ComponentBasics::operator=(comp);

        auto &p = dynamic_cast<const ComponentRotatable &>(comp);     
        // 拷贝theta
        Lewzen::ComponentRotatable::set_theta(p.getTheta());
        Lewzen::ComponentRotatable::set_rotate_center(p.getRotateCenter());
        Lewzen::ComponentRotatable::update_transform();

        return *this;
    }
    // 序列化，并记录已操作的
    void ComponentRotatable::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        ComponentBasics::serialize(j, processed);

        // 序列化theta
        j["theta"] = getTheta();
    }
    // 反序列化
    ComponentAbstract &ComponentRotatable::operator=(const json &j) {
        // 父类反序列化
        ComponentBasics::operator=(j);

        // 反序列化theta
        setTheta(j["theta"]);

        return *this;
    }
    // 事件
    // 父亲更换事件
    void ComponentRotatable::onParentChanged(const std::weak_ptr<ComponentAbstract> &prev, const std::weak_ptr<ComponentAbstract> &now) {
        if (isRotateBinded()) {
            auto p = prev.lock(), n = now.lock();
            std::shared_ptr<ComponentRotatable> pr, nr;
            if (!p || !p->moduleContains("Rotatable")) pr = std::shared_ptr<ComponentRotatable>(nullptr);
            else pr = std::dynamic_pointer_cast<ComponentRotatable>(p);
            if (!n || !n->moduleContains("Rotatable")) nr = std::shared_ptr<ComponentRotatable>(nullptr);
            else nr = std::dynamic_pointer_cast<ComponentRotatable>(n);
            rotateRelinkEvent(pr, nr); // 重链接
        }
    }

    //// Basics虚接口
    // 移动组件
    void ComponentRotatable::move(const double &dx, const double &dy) {
        auto delta = (getRotateBindParent()) ? 
            getRotateBindParent()->vectorFromCanvas(Lewzen::canvas_point(dx, dy)) :
            Lewzen::canvas_point(dx, dy); // 计算组件坐标系的Δ （组件坐标系转父坐标系）
        for (auto &p : getCorePoints()) {
            if (auto pp = p.lock()) {
                *pp += createPoint(delta.get_x(), delta.get_y());
            }
        }
        onMoved(dx, dy); // 移动后操作
        onChanged(); // 更新事件
    }
    // 移动组件到
    void ComponentRotatable::moveTo(const double &x, const double &y) {
        auto delta = Lewzen::canvas_point(x, y) - getCenter(); // 计算画布坐标系的Δ
        move(delta.get_x(), delta.get_y()); // 等价移动
    }
    // 移动关键点
    void ComponentRotatable::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(dx, dy)); // 计算组件坐标系的Δ
        // 具体更新不实现
        // ...
        onRotateCenterChanged(); // 使得更新过程中不变的部分显示在原本的位置
        onChanged(); // 更新事件
    }
    // 删除关键点
    void ComponentRotatable::removeCorePoint(const std::string &id) {
        if (!corePoints.count(id)) return;
        corePoints[id]->on_remove();
        onRotateCenterChanged(); // 使得更新过程中不变的部分显示在原本的位置
        onChanged(); // 更新事件
    }

    //// Rotatable接口
    // 获取旋转角度
    double ComponentRotatable::getTheta() const {
        return Lewzen::ComponentRotatable::get_theta();
    }
    double ComponentRotatable::getCanvasTheta() const {
        double theta = getTheta();
        for (auto &a : getRotateBindAncestors()) theta += a->getTheta();
        return theta;
    }
    // 设置旋转角度
    void ComponentRotatable::setTheta(double theta) {
        // 应用旋转角度
        Lewzen::ComponentRotatable::set_theta(std::fmod(theta, 2 * PI));
        onRotateStatusChanged(); // 旋转状态改变
        onChanged(); // 更新事件
    }
    // 获取旋转中心：默认为图形中心
    Lewzen::Point2D ComponentRotatable::getRotateCenter() const {
        if (corePoints.size() == 0) return createPoint(0, 0);
        std::vector<std::shared_ptr<Lewzen::Point2D>> points;
        for (auto &p : corePoints) points.push_back(p.second);
        return Lewzen::geometry_centroid(points);
    }
    // 旋转状态改变
    void ComponentRotatable::onRotateStatusChanged() {
        rotateBindEvent();
    }
    // 旋转中心变换后操作 (旋转偏移)
    void ComponentRotatable::onRotateCenterChanged() {
        auto target = pointToCanvas(getRotateCenter()); // 中心应当所在的绝对位置
        onRotateStatusChanged(); // 旋转状态改变
        moveTo(target.get_x(), target.get_y()); // 旋转偏移
    }
    bool ComponentRotatable::isRotateBinded() const {
        return rotateBinded;
    }
    void ComponentRotatable::setRotateBinded(bool binded) {
        if (binded == rotateBinded) return;
        if (binded) {
            rotateBinded = binded;
            rotateRelinkEvent(std::shared_ptr<ComponentRotatable>(nullptr), getRotateBindParent());
        } else {
            auto rp = getRotateBindParent(); rotateBinded = binded;
            rotateRelinkEvent(rp, std::shared_ptr<ComponentRotatable>(nullptr));            
        }
    }
    // 获取父旋转绑定组件
    std::shared_ptr<ComponentRotatable> ComponentRotatable::getRotateBindParent() const {
        if (isRotateBinded() && getParent() && getParent()->moduleContains("Rotatable")) {
            return std::dynamic_pointer_cast<ComponentRotatable>(getParent());
        }
        return std::shared_ptr<ComponentRotatable>(nullptr);
    }
    // 获取祖先旋转绑定组件; 不包括自己
    std::vector<std::shared_ptr<ComponentRotatable>> ComponentRotatable::getRotateBindAncestors() const {
        std::vector<std::shared_ptr<ComponentRotatable>> vec;
        auto comp = std::dynamic_pointer_cast<const ComponentRotatable>(shared_from_this());
        while (auto p = comp->getParent()) {
            if (!comp->isRotateBinded() || !p->moduleContains("Rotatable")) break;
            auto pp = std::dynamic_pointer_cast<ComponentRotatable>(p);
            vec.push_back(pp);
            comp = pp;
        }
        return std::move(vec);
    }
    // 是祖先旋转绑定组件 (包括自己)
    bool ComponentRotatable::isRotateBindAncestorOf(const std::weak_ptr<ComponentRotatable> &component) const {
        auto comp = component.lock();
        while (comp) {
            if (comp == shared_from_this()) return true;
            comp = comp->getRotateBindParent();
        }
        return false;
    }
    // 获取旋转绑定顶级节点
    std::vector<std::shared_ptr<ComponentRotatable>> ComponentRotatable::extractRotateBindTop(const std::vector<std::shared_ptr<ComponentRotatable>> &components) {
        std::set<int> not_top;
        int n = components.size();
        for (int i = 0; i < n; i++) {
            if (not_top.count(i)) continue;
            for (int j = i + 1; j < n; j++) {
                if (not_top.count(j)) continue;
                auto &a = components[i];
                auto &b = components[j];
                if (a->isRotateBindAncestorOf(b)) not_top.insert(j); // a是b的祖先，b不是顶级节点
                else if (b->isRotateBindAncestorOf(a)) not_top.insert(i); // b是a的祖先，a不是顶级节点
            }
        }
        std::vector<std::shared_ptr<ComponentRotatable>> vec;
        for (int i = 0; i < n; i++) if (!not_top.count(i)) vec.push_back(components[i]);
        return std::move(vec);
    }
    // 移动绑定事件
    void ComponentRotatable::moveBindEvent(const double &dx, const double &dy) {
        // 记录原位置
        std::map<std::string, std::pair<double, double>> mp;
        for (auto c : getChildren()) if (c->moduleContains("Rotatable")) {
            auto cb = std::dynamic_pointer_cast<ComponentRotatable>(c);
            auto cp = cb->pointToCanvas(cb->getRotateCenter());
            mp[cb->getId()] = { cp.get_x(), cp.get_y() };
        }
        onRotateStatusChanged(); // 旋转状态改变
        // 回到原位置
        for (auto c : getChildren()) if (c->moduleContains("Rotatable")) {
            auto cb = std::dynamic_pointer_cast<ComponentRotatable>(c);
            auto cp = mp[cb->getId()];
            auto np = cb->pointToCanvas(cb->getRotateCenter());
            cb->move(cp.first - np.get_x(), cp.second - np.get_y()); // 反向移动
        }
        ComponentBasics::moveBindEvent(dx, dy);
    }
    // 旋转绑定事件
    void ComponentRotatable::rotateBindEvent() {
        set_rotate_center(getRotateCenter());
        Lewzen::ComponentRotatable::update_transform();
        for (auto c : getChildren()) if (c->moduleContains("Rotatable")) { // 绑定旋转，遍历合法孩子进行旋转
            auto cb = std::dynamic_pointer_cast<ComponentRotatable>(c);
            if (cb->isRotateBinded()) cb->setTheta(cb->getTheta());
        }
    }
    // 旋转重链接事件
    void ComponentRotatable::rotateRelinkEvent(const std::shared_ptr<ComponentRotatable> &prev, const std::shared_ptr<ComponentRotatable> &now) {
        auto theta = getTheta(); auto zero = getRotateCenter();
        // 将组件从在旧父组件坐标系下转化为在画布坐标系下
        if (prev) {
            // 旋转中心转为画布坐标系
            auto zero_c = prev->pointToCanvas(prev->createPoint(zero.get_x(), zero.get_y()));
            zero.set_x(zero_c.get_x()), zero.set_y(zero_c.get_y());
            // 角度转为画布坐标系
            theta += prev->getCanvasTheta();
        }
        // 将组件从在画布坐标系下转化为在新的父组件坐标系下
        if (now) {
            // 角度转为组件坐标系
            theta -= now->getCanvasTheta();
        }
        setTheta(theta);
        moveTo(zero.get_x(), zero.get_y()); // 移动到
    }
}