#ifndef __LEWZENSERVER_COMP_BASICS__
#define __LEWZENSERVER_COMP_BASICS__
#include "comp_abstract.h"
#include "../register.h"

namespace LewzenServer {
    class ComponentBasics : virtual public ComponentAbstract {
    private:
        static bool registered;
        const std::string module_type = "Basics";
    protected:
        // 关键点列表
        std::unordered_map<std::string, std::shared_ptr<CorePoint>> corePoints;
        // SVGI
        std::shared_ptr<Lewzen::SVGIG> SVGIG;
        // Defs
        std::vector<std::weak_ptr<Lewzen::SVGIElement>> Defs;
        // 注册接口
        void registering();
        
        // 设置所有关键点
        void setCorePoints(const std::vector<std::shared_ptr<CorePoint>> &corePointList);
        // 父移动绑定
        bool moveBinded = true;
    public:
        //// 基本接口
        // 构造
        ComponentBasics();

        //// 通用虚接口
        // 获取所有关键点
        virtual std::vector<std::weak_ptr<CorePoint>> getCorePoints() const;
        // 获取维护的SVGI
        virtual std::weak_ptr<Lewzen::SVGIElement> getSVGI() const;
        // 获取需要的Defs
        virtual std::vector<std::weak_ptr<Lewzen::SVGIElement>> getDefs() const;
        // 获取图形中心
        virtual Lewzen::Point2D getCenter() const;
        // 获取坐标系
        virtual const std::shared_ptr<Lewzen::CoordinateSystem> getCoordinateSystem() const;
        // 移动组件到
        virtual void moveTo(const double &x, const double &y);
        // 非构造初始化
        virtual void init();
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp);
        // 克隆
        std::shared_ptr<ComponentAbstract> clone();
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed);
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j);
        // 事件
        virtual void onAdded();
        virtual void onChanged();
        virtual void onRemoved();
        virtual void onReadded();
        virtual void onDiscarded();
        virtual void onParentChanged(const std::weak_ptr<ComponentAbstract> &prev, const std::weak_ptr<ComponentAbstract> &now);
        virtual void onChildAdded(const std::weak_ptr<ComponentAbstract> &child);
        virtual void onChildRemoved(const std::weak_ptr<ComponentAbstract> &child);
        
        //// Basics接口
        // 调整层级
        void forward();
        void backward();
        void front();
        void back();
        // 移动变换后操作
        virtual void onMoved(const double &dx, const double &dy);
        // 移动绑定
        bool isMoveBinded() const;
        void setMoveBinded(bool binded);
        // 获取父可移动组件
        std::shared_ptr<ComponentBasics> getMoveBindParent() const;
        // 获取祖先可移动组件; 不包括自己
        std::vector<std::shared_ptr<ComponentBasics>> getMoveBindAncestors() const;
        // 是祖先可移动组件 (包括自己)
        bool isMoveBindAncestorOf(const std::weak_ptr<ComponentBasics> &component) const;
        // 获取移动绑定顶级节点
        static std::vector<std::shared_ptr<ComponentBasics>> extractMoveBindTop(const std::vector<std::shared_ptr<ComponentBasics>> &components);
        // 移动绑定事件
        virtual void moveBindEvent(const double &dx, const double &dy);

        //// Basics虚接口
        // 移动组件
        virtual void move(const double &dx, const double &dy);
        // 移动关键点
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy);
        // 删除关键点
        virtual void removeCorePoint(const std::string &id);
    };
}
#endif