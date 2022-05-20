#ifndef __LEWZENSERVER_COMP_FLIPPABLE__
#define __LEWZENSERVER_COMP_FLIPPABLE__
#include "comp_abstract.h"

namespace LewzenServer {
    class ComponentFlippable : virtual public ComponentAbstract {
    private:
        static bool registered;
        const std::string module_type = "Flippable";
    protected:
        // 注册接口
        void registering();
        // 父翻转绑定
        bool flipBinded = true;
    public:
        ComponentFlippable();

        //// Flippable接口
        // 翻转
        virtual void flip(const double &a, const double &b, const double &c) = 0;
        // 翻转变换后操作
        virtual void onFlipped(const double &a, const double &b, const double &c);
        // 翻转绑定
        bool isFlipBinded() const;
        void setFlipBinded(bool binded);
        // 获取父可翻转组件
        std::shared_ptr<ComponentFlippable> getFlipBindParent() const;
        // 获取祖先可翻转组件; 不包括自己
        std::vector<std::shared_ptr<ComponentFlippable>> getFlipBindAncestors() const;
        // 是祖先可翻转组件 (包括自己)
        bool isFlipBindAncestorOf(const std::weak_ptr<ComponentFlippable> &component) const;
        // 获取翻转绑定顶级节点
        static std::vector<std::shared_ptr<ComponentFlippable>> extractFlipBindTop(const std::vector<std::shared_ptr<ComponentFlippable>> &components);
        // 翻转绑定事件
        virtual void flipBindEvent(const double &a, const double &b, const double &c);
    };
}
#endif