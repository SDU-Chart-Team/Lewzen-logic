#ifndef __LEWZENSERVER_COMP_SCALABLE__
#define __LEWZENSERVER_COMP_SCALABLE__
#include "comp_abstract.h"

namespace LewzenServer {
    class ComponentScalable : virtual public ComponentAbstract {
    private:
        static bool registered;
        const std::string module_type = "Scalable";
    protected:
        // 注册接口
        void registering();
        // 父缩放绑定
        bool scaleBinded = false;
    public:
        ComponentScalable();

        //// Scalable接口
        // 缩放
        virtual void scale(const double &scaleX, const double &scaleY) = 0;
        // 大小变换后操作
        virtual void onScaleChanged(const Lewzen::Point2D &lastCenter, const double &scaleX, const double &scaleY);
        // 缩放绑定
        bool isScaleBinded() const;
        void setScaleBinded(bool binded);
        // 获取父可缩放组件
        std::shared_ptr<ComponentScalable> getScaleBindParent() const;
        // 获取祖先可缩放组件; 不包括自己
        std::vector<std::shared_ptr<ComponentScalable>> getScaleBindAncestors() const;
        // 是祖先可缩放组件 (包括自己)
        bool isScaleBindAncestorOf(const std::weak_ptr<ComponentScalable> &component) const;
        // 获取缩放绑定顶级节点
        static std::vector<std::shared_ptr<ComponentScalable>> extractScaleBindTop(const std::vector<std::shared_ptr<ComponentScalable>> &components);
        // 缩放绑定事件
        virtual void scaleBindEvent(const Lewzen::Point2D &lastCenter, const double &scaleX, const double &scaleY);
    };
}
#endif