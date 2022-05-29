#ifndef __LEWZENSERVER_canvas__
#define __LEWZENSERVER_canvas__
#include <utility>
#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include "comp_factory.h"
#include "utils/kv_heap.hpp"
#include "release/lewzen-core/core.h"

namespace LewzenServer {
    class Canvas {
    private:
        static std::shared_ptr<Lewzen::SVGISvg> svg; // <svg>
        static std::shared_ptr<Lewzen::SVGIDefs> defs; // <defs>
        static std::shared_ptr<Lewzen::SVGIG> els; // <g>
    public:
        static std::unordered_map<std::string, std::shared_ptr<ComponentAbstract>> components; // 当前组件集合
        static const std::string HTML();
    private:
        static std::unordered_map<Lewzen::HASH_CODE, int> defs_counter; // defs计数器
        static void _component_added(const std::shared_ptr<ComponentAbstract> &);
        static void _component_removed(const std::shared_ptr<ComponentAbstract> &);
        static std::multimap<int, std::shared_ptr<ComponentAbstract>> removed; // 暂存区
        static std::unordered_map<Lewzen::HASH_CODE, int> removed_layer; // 暂存区组件层级

        // 层级、树形关系管理中的过程量
        static std::vector<std::string> added_comp_ids;
        static std::vector<std::string> removed_comp_ids;
        static std::unordered_map<std::string, int> readded_layer_map;
        static std::vector<std::pair<std::string, std::string>> copied_comp_pairs;
    public:
        static const std::string init();
    
    //// 用于注册器
    public:
        // 增加组件
        static std::shared_ptr<ComponentAbstract> add(const std::string &type);
        static void add(std::weak_ptr<ComponentAbstract> comp);
        // 指向组件
        static std::weak_ptr<ComponentAbstract> cursor(const std::string &id);
        // 指向多个组件
        static std::vector<std::weak_ptr<ComponentAbstract>> cursors(const std::vector<std::string> &ids);
        // 暂时移除组件
        static void remove(const int &time);
        static void remove(std::weak_ptr<ComponentAbstract> comp, const int &time);
        // 复制组件
        static void copy();
        static std::shared_ptr<ComponentAbstract> copy(std::weak_ptr<ComponentAbstract> comp);
        // 重新增加组件
        static void readd();
        static void readd(std::weak_ptr<ComponentAbstract> comp);
        // 丢弃组件
        static bool discard(const int &time);
        // 序列化
        static const json serialize();
        // 反序列化
        static void deserialize(const json &j);
        // 获取被添加的组件信息
        static void getAddedComponents(std::vector<std::string> &ids, std::vector<std::string> &tops);
        // 获取被移除的组件信息
        static void getRemovedComponents(std::vector<std::string> &ids);
    
    //// 用于层级变化
    public:
        // 获取层级
        static int getLayer(const std::string &id);
        // 设置层级
        static bool setLayer(const std::string &id, int layer);
        // 向前
        static bool forward(const std::string &id);
        // 向后
        static bool backward(const std::string &id);
        // 最前
        static bool front(const std::string &id);
        // 最后
        static bool back(const std::string &id);
    
    //// 用于画布变化
    private:
        using CPHeap = kv_heap::KVHeap<double>;
        static int x, y, width, height; //画布ViewBox
         // 维护关键点坐标上下界
        static CPHeap infX, infY, supX, supY;

        static void updateViewBoxFromComponent(std::weak_ptr<ComponentAbstract> component);
        static void setCanvasTranslate();
    public:
        static const int A4WIDTH, A4HEIGHT;
        // 更新画布大小
        static void updateViewBox(const std::weak_ptr<ComponentAbstract> &component);

    //// 用于提交
    public:
        // 提交DOM Commands, 只影响了一个组件
        static const std::string commit();
    };
}
#endif
