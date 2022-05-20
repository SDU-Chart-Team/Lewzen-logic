#include "comp_stylized.h"
#include "../canvas.h"

namespace LewzenServer {
    bool ComponentStylized::registered = false;
    // 注册接口
    void ComponentStylized::registering() {
        Register::addEvent("get_style", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentStylized>(cursor); // 动态类型转换
                param["style"] = comp->getStyle();
                param["status"] = SUCCEED;
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                std::string style;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentStylized>(cursor); // 动态类型转换
                    if (!matched) style = comp->getStyle(), matched = true;
                    else if (style != comp->getStyle()) {
                        matched = false;
                        break;
                    }
                }
                if (matched) {
                    param["style"] = style;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("set_style", [&](json &param) {
            auto style = param["style"];
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentStylized>(cursor); // 动态类型转换
                comp->setStyle(style);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentStylized>(cursor); // 动态类型转换
                    comp->setStyle(style);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
    }

    ComponentStylized::ComponentStylized() {
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
    }

    //// 通用虚接口
    // 非构造初始化
    void ComponentStylized::init() {
        if (auto svgi = getSVGI().lock()) svgi->Style.bind(std::bind(&ComponentStylized::getStyle, this));
    }
    // 拷贝
    ComponentAbstract &ComponentStylized::operator=(const ComponentAbstract &comp) {
        auto &p = dynamic_cast<const ComponentStylized &>(comp);     
        // 拷贝style
        _style = p._style;
    }
    // 序列化，并记录已操作的
    void ComponentStylized::serialize(json &j, std::vector<std::string> &processed) {
        j["style"] = _style;
    }
    // 反序列化
    ComponentAbstract &ComponentStylized::operator=(const json &j) {
        // 反序列化style
        _style = j["style"];
    }

    //// Stylized接口
    // 获取样式
    const std::string ComponentStylized::getStyle() {
        return _style;
    }
    // 设置样式
    void ComponentStylized::setStyle(const std::string &style) {
        _style = style;
    }
}