#ifndef __LEWZENSERVER_COMP_STYLIZED__
#define __LEWZENSERVER_COMP_STYLIZED__
#include "comp_abstract.h"

namespace LewzenServer {
    class ComponentStylized : virtual public ComponentAbstract {
    private:
        static bool registered;
        const std::string module_type = "Stylized";
    protected:
        // 注册接口
        void registering();
        // 样式表
        std::string _style;
    public:
        ComponentStylized();

        //// 通用虚接口
        // 非构造初始化
        virtual void init();
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp);
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed);
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j);

        //// Stylized接口
        // 获取样式
        const std::string getStyle();
        // 设置样式
        void setStyle(const std::string &style);
    };
}
#endif