#ifndef __LEWZENSERVER_COMP_ABSTRACT__
#define __LEWZENSERVER_COMP_ABSTRACT__
#include "../release/lewzen-core/core.h"
#include "../utils/uuid.h"
#include "../utils/json.hpp"
#include "core_point.h"
#include <string>
#include <set>
#include <vector>
#include <memory>

namespace LewzenServer {
    class ComponentAbstract : public std::enable_shared_from_this<ComponentAbstract> {
    private:
        // 固有属性
        std::string _type;
        std::set<std::string> _modules;
        std::string _id;
        // 树形关系
        std::weak_ptr<ComponentAbstract> parent;
        std::set<std::shared_ptr<ComponentAbstract>> children;
    protected:
        // 添加模块类型
        void addModuleTypes(const std::string &module);
        // 设置组件类型
        void setType(const std::string &type);
    public:
        //// 基本接口
        // 构造
        ComponentAbstract ();
        // 获取Id
        const std::string getId() const;
        // 虚构造函数
        virtual ~ComponentAbstract() = default;
        
        //// 通用接口
        // 获取模块类型
        const std::set<std::string> getModuleTypes() const;
        // 查看模块类型是否存在
        bool moduleContains(const std::string &module) const;
        // 获取组件类型
        const std::string getType() const;
        // 获取子节点
        std::vector<std::shared_ptr<ComponentAbstract>> getChildren() const;
        // 获取父节点
        std::shared_ptr<ComponentAbstract> getParent() const;
        // 获取所有祖先; 不包含自己
        std::vector<std::shared_ptr<ComponentAbstract>> getAncestors() const;
        // 获取所有后代
        std::vector<std::shared_ptr<ComponentAbstract>> getDescendants() const;
        // 是祖先（包括自己）
        bool isAncestorOf(const std::weak_ptr<ComponentAbstract> &component) const;
        // 获取顶级节点
        static std::vector<std::shared_ptr<ComponentAbstract>> extractTop(const std::vector<std::shared_ptr<ComponentAbstract>> &components);
        // 增加子节点
        void addChild(const std::weak_ptr<ComponentAbstract> &child);
        // 移除子节点
        void removeChild(const std::weak_ptr<ComponentAbstract> &child);
        // 创建该坐标系下的点
        Lewzen::Point2D createPoint() const;
        Lewzen::Point2D createPoint(const double &x, const double &y) const;
        // 创建一个关键点
        std::shared_ptr<CorePoint> createCorePoint(const std::string &id) const;
        std::shared_ptr<CorePoint> createCorePoint(const std::string &id, const double &x, const double &y) const;

        //// 通用虚接口
        // 获取所有关键点
        virtual std::vector<std::weak_ptr<CorePoint>> getCorePoints() const = 0;
        // 获取维护的SVGI
        virtual std::weak_ptr<Lewzen::SVGIElement> getSVGI() const = 0;
        // 获取需要的Defs
        virtual std::vector<std::weak_ptr<Lewzen::SVGIElement>> getDefs() const = 0;
        // 获取图形中心 (画布坐标系)
        virtual Lewzen::Point2D getCenter() const = 0;
        // 获取坐标系
        virtual const std::shared_ptr<Lewzen::CoordinateSystem> getCoordinateSystem() const = 0;
        // 移动组件到
        virtual void moveTo(const double &x, const double &y) = 0;
        // 非构造初始化
        virtual void init() = 0;
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) = 0;
        // 克隆
        virtual std::shared_ptr<ComponentAbstract> clone() = 0;
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) = 0;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) = 0;
        // 反序列化生成
        static std::shared_ptr<ComponentAbstract> deserialize(const json &j);
        // 事件
        virtual void onAdded() = 0;
        virtual void onChanged() = 0;
        virtual void onRemoved(int time) = 0;
        virtual void onReadded(int time) = 0;
        virtual void onDiscarded() = 0;
        virtual void onParentChanged(const std::weak_ptr<ComponentAbstract> &prev, const std::weak_ptr<ComponentAbstract> &now) = 0;
        virtual void onChildAdded(const std::weak_ptr<ComponentAbstract> &child) = 0;
        virtual void onChildRemoved(const std::weak_ptr<ComponentAbstract> &child) = 0;
    };
}
#endif