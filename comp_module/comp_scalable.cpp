#include "comp_scalable.h"
#include "../canvas.h"

namespace LewzenServer {
    bool ComponentScalable::registered = false;
    // 注册接口
    void ComponentScalable::registering() {
        Register::addEvent("get_scale_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentScalable>(cursor); // 动态类型转换
                param["status"] = SUCCEED;
                param["scale_bind"] = comp->isScaleBinded();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                double binded = 0;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentScalable>(cursor); // 动态类型转换
                    if (!matched) binded = comp->isScaleBinded(), matched = true;
                    else if (binded != comp->isScaleBinded()) { // 多值
                        matched = false;
                        break;
                    }
                }
                if (matched) {
                    param["scale_bind"] = binded;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("enable_scale_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentScalable>(cursor); // 动态类型转换
                comp->setScaleBinded(true);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentScalable>(cursor); // 动态类型转换
                    comp->setScaleBinded(true);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("disable_scale_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentScalable>(cursor); // 动态类型转换
                comp->setScaleBinded(false);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentScalable>(cursor); // 动态类型转换
                    comp->setScaleBinded(false);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
    }

    ComponentScalable::ComponentScalable() {
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
    }

    //// Scalable接口
    // 大小变换后操作
    void ComponentScalable::onScaleChanged(const Lewzen::Point2D &lastCenter, const double &scaleX, const double &scaleY) {
        scaleBindEvent(lastCenter, scaleX, scaleY);
    }
    // 缩放绑定
    bool ComponentScalable::isScaleBinded() const {
        return scaleBinded;
    }
    void ComponentScalable::setScaleBinded(bool binded) {
        scaleBinded = binded;
    }
    // 获取父可缩放组件
    std::shared_ptr<ComponentScalable> ComponentScalable::getScaleBindParent() const {
        if (isScaleBinded() && getParent() && getParent()->moduleContains("Scalable")) {
            return std::dynamic_pointer_cast<ComponentScalable>(getParent());
        }
        return std::shared_ptr<ComponentScalable>(nullptr);
    }
    // 获取祖先可缩放组件; 不包括自己
    std::vector<std::shared_ptr<ComponentScalable>> ComponentScalable::getScaleBindAncestors() const {
        std::vector<std::shared_ptr<ComponentScalable>> vec;
        auto comp = std::dynamic_pointer_cast<const ComponentScalable>(shared_from_this());
        while (auto p = comp->getParent()) {
            if (!comp->isScaleBinded() || !p->moduleContains("Scalable")) break;
            vec.push_back(std::dynamic_pointer_cast<ComponentScalable>(p));
        }
        return std::move(vec);
    }
    // 是祖先可缩放组件 (包括自己)
    bool ComponentScalable::isScaleBindAncestorOf(const std::weak_ptr<ComponentScalable> &component) const {
        auto comp = component.lock();
        while (comp) {
            if (comp == shared_from_this()) return true;
            comp = comp->getScaleBindParent();
        }
        return false;
    }
    // 获取缩放绑定顶级节点
    std::vector<std::shared_ptr<ComponentScalable>> ComponentScalable::extractScaleBindTop(const std::vector<std::shared_ptr<ComponentScalable>> &components) {
        std::set<int> not_top;
        int n = components.size();
        for (int i = 0; i < n; i++) {
            if (not_top.count(i)) continue;
            for (int j = i + 1; j < n; j++) {
                if (not_top.count(j)) continue;
                auto &a = components[i];
                auto &b = components[j];
                if (a->isScaleBindAncestorOf(b)) not_top.insert(j); // a是b的祖先，b不是顶级节点
                else if (b->isScaleBindAncestorOf(a)) not_top.insert(i); // b是a的祖先，a不是顶级节点
            }
        }
        std::vector<std::shared_ptr<ComponentScalable>> vec;
        for (int i = 0; i < n; i++) if (!not_top.count(i)) vec.push_back(components[i]);
        return std::move(vec);
    }
    // 缩放绑定事件
    void ComponentScalable::scaleBindEvent(const Lewzen::Point2D &lastCenter, const double &scaleX, const double &scaleY) {
        for (auto c : getChildren()) if (c->moduleContains("Scalable")) { // 绑定移动，遍历合法孩子进行移动
            auto cb = std::dynamic_pointer_cast<ComponentScalable>(c);
            if (cb->isScaleBinded()) {
                auto delta = ((cb->getCenter())(getCoordinateSystem()) - lastCenter(getCoordinateSystem()));
                delta.set_x(delta.get_x() * scaleX), delta.set_y(delta.get_y() * scaleY);
                auto dest = ((cb->getCenter())(getCoordinateSystem()) + delta)(Lewzen::CanvasCoordinateSystem::canvas_coordinate_system); // 计算在画布上的最终维护
                cb->moveTo(dest.get_x(), dest.get_y()); // 移动到指定位置
                cb->scale(scaleX, scaleY); // 进行缩放
            }
        }
    }
}