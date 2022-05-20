#ifndef __LEWZENSERVER_REGISTER__
#define __LEWZENSERVER_REGISTER__
#include "comp_module/comp_abstract.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <functional>
#include <vector>
#include <map>

namespace LewzenServer {
    // 常量
    const static std::string ILLEGAL = "!illegal";
    const static std::string IFAILED = "!ifailed";
    const static std::string NTARGET = "!ntarget";
    const static std::string NULLREG = "!nullreg";
    const static std::string NULLPTR = "!nullptr";
    const static std::string NULLCMD = "!nullcmd";
    const static std::string EMPTYRT = "!emptyrt";
    const static std::string MULTIVL = "!multivl";
    const static std::string SUCCEED = "!succeed";

    class ComponentAbstract;

    class Register {
    private:
        // 单组件游标
        static bool selected;
        static std::weak_ptr<ComponentAbstract> cursor;
        static std::shared_ptr<ComponentAbstract> selected_with(const std::string &module);
        // 多组件游标
        static bool multi_selected;
        static std::vector<std::weak_ptr<ComponentAbstract>> cursors;
        static std::vector<std::shared_ptr<ComponentAbstract>> multi_selected_with(const std::string &module);

        // 接口映射
        static std::map<std::string, std::function<const json(json &)>> events;

        // 注册自己
        static void registering();
    public:
        // 初始化
        static const std::string init();

        // 添加命令
        static void addEvent(const std::string &interface_name,
            std::function<const json(json &)> interface_body);
        // 运行命令
        static const std::string run(const std::string &cmd);
        
        // 切换器
        static void switchCursorOnly(json &j, const std::string &module_type,
            std::function<void(std::shared_ptr<ComponentAbstract> &)> doSomething);
        static void switchMultiCursorOnly(json &j, const std::string &module_type,
            std::function<void(std::vector<std::shared_ptr<ComponentAbstract>> &)> doSomething);
        static void switchBoth(json &j, const std::string &module_type,
            std::function<void(std::shared_ptr<ComponentAbstract> &)> doSomethingA,
            std::function<void(std::vector<std::shared_ptr<ComponentAbstract>> &)> doSomethingB);

        // 实用方法
        static void listComponentId(json &j, const std::vector<std::weak_ptr<ComponentAbstract>> &list);
        static void listComponentId(json &j, const std::set<std::shared_ptr<ComponentAbstract>> &set);
    };
}
#endif