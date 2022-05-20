#include "comp_flippable.h"
#include "../canvas.h"

namespace LewzenServer {
    bool ComponentFlippable::registered = false;
    // 注册接口
    void ComponentFlippable::registering() {
        Register::addEvent("flip", [&](json &param) {
            double a = param["a"], b = param["b"], c = param["c"];
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentFlippable>(cursor); // 动态类型转换
                comp->flip(a, b, c);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                std::vector<std::shared_ptr<ComponentFlippable>> vec;
                for (auto cursor : cursors) vec.push_back(std::dynamic_pointer_cast<ComponentFlippable>(cursor)); // 动态类型转换
                for (auto comp : extractFlipBindTop(vec)) comp->flip(a, b, c); // 仅应用顶级翻转绑定组件
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_flip_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentFlippable>(cursor); // 动态类型转换
                param["status"] = SUCCEED;
                param["flip_bind"] = comp->isFlipBinded();
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                double binded = 0;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentFlippable>(cursor); // 动态类型转换
                    if (!matched) binded = comp->isFlipBinded(), matched = true;
                    else if (binded != comp->isFlipBinded()) { // 多值
                        matched = false;
                        break;
                    }
                }
                if (matched) {
                    param["flip_bind"] = binded;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("enable_flip_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentFlippable>(cursor); // 动态类型转换
                comp->setFlipBinded(true);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentFlippable>(cursor); // 动态类型转换
                    comp->setFlipBinded(true);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("disable_flip_bind", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentFlippable>(cursor); // 动态类型转换
                comp->setFlipBinded(false);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentFlippable>(cursor); // 动态类型转换
                    comp->setFlipBinded(false);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
    }

    ComponentFlippable::ComponentFlippable() {
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
    }

    //// Flippable接口
    // 翻转变换后操作
    void ComponentFlippable::onFlipped(const double &a, const double &b, const double &c) {
        auto C = getCenter();
        double c_ = - (a * C.get_x() + b * C.get_y());
        flipBindEvent(a, b, c_);
    }
    // 翻转绑定
    bool ComponentFlippable::isFlipBinded() const {
        return flipBinded;
    }
    void ComponentFlippable::setFlipBinded(bool binded) {
        flipBinded = binded;
    }
    // 获取父可翻转组件
    std::shared_ptr<ComponentFlippable> ComponentFlippable::getFlipBindParent() const {
        if (isFlipBinded() && getParent() && getParent()->moduleContains("Flippable")) {
            return std::dynamic_pointer_cast<ComponentFlippable>(getParent());
        }
        return std::shared_ptr<ComponentFlippable>(nullptr);
    }
    // 获取祖先可翻转组件; 不包括自己
    std::vector<std::shared_ptr<ComponentFlippable>> ComponentFlippable::getFlipBindAncestors() const {
        std::vector<std::shared_ptr<ComponentFlippable>> vec;
        auto comp = std::dynamic_pointer_cast<const ComponentFlippable>(shared_from_this());
        while (auto p = comp->getParent()) {
            if (!comp->isFlipBinded() || !p->moduleContains("Flippable")) break;
            vec.push_back(std::dynamic_pointer_cast<ComponentFlippable>(p));
        }
        return std::move(vec);
    }
    // 是祖先可翻转组件 (包括自己)
    bool ComponentFlippable::isFlipBindAncestorOf(const std::weak_ptr<ComponentFlippable> &component) const {
        auto comp = component.lock();
        while (comp) {
            if (comp == shared_from_this()) return true;
            comp = comp->getFlipBindParent();
        }
        return false;
    }
    // 获取翻转绑定顶级节点
    std::vector<std::shared_ptr<ComponentFlippable>> ComponentFlippable::extractFlipBindTop(const std::vector<std::shared_ptr<ComponentFlippable>> &components) {
        std::set<int> not_top;
        int n = components.size();
        for (int i = 0; i < n; i++) {
            if (not_top.count(i)) continue;
            for (int j = i + 1; j < n; j++) {
                if (not_top.count(j)) continue;
                auto &a = components[i];
                auto &b = components[j];
                if (a->isFlipBindAncestorOf(b)) not_top.insert(j); // a是b的祖先，b不是顶级节点
                else if (b->isFlipBindAncestorOf(a)) not_top.insert(i); // b是a的祖先，a不是顶级节点
            }
        }
        std::vector<std::shared_ptr<ComponentFlippable>> vec;
        for (int i = 0; i < n; i++) if (!not_top.count(i)) vec.push_back(components[i]);
        return std::move(vec);
    }
    // 翻转绑定事件
    void ComponentFlippable::flipBindEvent(const double &a, const double &b, const double &c) {
        for (auto ch : getChildren()) if (ch->moduleContains("Flippable")) { // 绑定移动，遍历合法孩子进行移动
            auto cb = std::dynamic_pointer_cast<ComponentFlippable>(ch);
            if (cb->isFlipBinded()) {
                cb->flip(a, b, c); // 进行翻转
            }
        }
    }
}