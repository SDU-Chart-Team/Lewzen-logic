#ifndef __LEWZENSERVER_COMP_ROTATABLE__
#define __LEWZENSERVER_COMP_ROTATABLE__
#include "comp_basics.h"

namespace LewzenServer {
    class ComponentRotatable : virtual public ComponentBasics, virtual public Lewzen::ComponentRotatable {
    private:
        static bool registered;
        const std::string module_type = "Rotatable";
        // 父可旋转组件
        virtual std::weak_ptr<Lewzen::ComponentRotatable> get_parent() const override;
        // 获取坐标系
        virtual const std::shared_ptr<Lewzen::CoordinateSystem> get_coordinate_system() const override;
        // 隐藏
        using Lewzen::ComponentRotatable::create_point;
        using Lewzen::ComponentRotatable::from_canvas;
        using Lewzen::ComponentRotatable::to_canvas;
        using Lewzen::ComponentRotatable::get_area_vertex;
        using Lewzen::ComponentRotatable::set_area_vertex;
        using Lewzen::ComponentRotatable::get_rotate_center;
        using Lewzen::ComponentRotatable::set_rotate_center;
        using Lewzen::ComponentRotatable::get_svg_element_interface;
        using Lewzen::ComponentRotatable::set_svg_element_interface;
        using Lewzen::ComponentRotatable::get_theta;
        using Lewzen::ComponentRotatable::set_theta;
        using Lewzen::ComponentRotatable::update_transform;
    protected:
        // 注册接口
        void registering();
        // 将组件向量转为画布向量
        Lewzen::Point2D vectorToCanvas(const Lewzen::Point2D& vector) const;
        // 将画布向量转为组件向量
        Lewzen::Point2D vectorFromCanvas(const Lewzen::Point2D& vector) const;
        // 将组件坐标转为画布坐标
        Lewzen::Point2D pointToCanvas(const Lewzen::Point2D& point) const;
        // 将画布坐标转为组件坐标
        Lewzen::Point2D pointFromCanvas(const Lewzen::Point2D& point) const;
        // 父旋转绑定
        bool rotateBinded = true;
    public:
        static constexpr long double PI = 3.141592653589793238462643383279502884L;
        ComponentRotatable();

        //// 通用虚接口
        // 获取坐标系
        virtual const std::shared_ptr<Lewzen::CoordinateSystem> getCoordinateSystem() const;
        // 获取图形中心
        virtual Lewzen::Point2D getCenter() const;
        // 非构造初始化
        virtual void init();
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp);
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed);
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j);
        // 事件
        virtual void onParentChanged(const std::weak_ptr<ComponentAbstract> &prev, const std::weak_ptr<ComponentAbstract> &now);

        //// Basics虚接口
        // 移动组件 (画布坐标系)
        virtual void move(const double &dx, const double &dy);
        // 移动组件到 (画布坐标系)
        virtual void moveTo(const double &x, const double &y);
        // 移动关键点 (画布坐标系)
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy);
        // 删除关键点
        virtual void removeCorePoint(const std::string &id);

        //// Rotatable接口
        // 获取旋转角度
        double getTheta() const;
        // 获取绝对旋转角度
        double getCanvasTheta() const;
        // 设置旋转角度
        void setTheta(double theta);
        // 获取旋转中心
        virtual Lewzen::Point2D getRotateCenter() const;
        // 旋转状态改变
        virtual void onRotateStatusChanged();
        // 旋转中心变换后操作 (旋转偏移)
        virtual void onRotateCenterChanged();
        // 旋转绑定
        bool isRotateBinded() const;
        void setRotateBinded(bool binded);
        // 获取父可旋转组件
        std::shared_ptr<ComponentRotatable> getRotateBindParent() const;
        // 获取祖先可旋转组件; 不包括自己
        std::vector<std::shared_ptr<ComponentRotatable>> getRotateBindAncestors() const;
        // 是祖先可旋转组件 (包括自己)
        bool isRotateBindAncestorOf(const std::weak_ptr<ComponentRotatable> &component) const;
        // 获取旋转绑定顶级节点
        static std::vector<std::shared_ptr<ComponentRotatable>> extractRotateBindTop(const std::vector<std::shared_ptr<ComponentRotatable>> &components);
        // 移动绑定事件
        virtual void moveBindEvent(const double &dx, const double &dy) override;
        // 旋转绑定事件
        virtual void rotateBindEvent();
        // 旋转重链接事件
        virtual void rotateRelinkEvent(const std::shared_ptr<ComponentRotatable> &prev, const std::shared_ptr<ComponentRotatable> &now);
    };
}
#endif