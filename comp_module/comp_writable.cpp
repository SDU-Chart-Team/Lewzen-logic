#include "comp_writable.h"
#include "../canvas.h"

namespace LewzenServer {
    bool ComponentWritable::registered = false;
    // 注册接口
    void ComponentWritable::registering() {
        Register::addEvent("get_spacing", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                auto &sp = comp->getSpacing();
                json j; j["top"] = sp.top, j["left"] = sp.left, j["bottom"] = sp.bottom, j["right"] = sp.right, j["global"] = sp.global;
                param["spacing"] = j;
                param["status"] = SUCCEED;
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                json j;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                    auto &sp = comp->getSpacing();
                    if (!matched) {
                        j["top"] = sp.top, j["left"] = sp.left, j["bottom"] = sp.bottom, j["right"] = sp.right, j["global"] = sp.global;
                        matched = true;
                    } else { // 多值
                        json b; b["top"] = sp.top, b["left"] = sp.left, b["bottom"] = sp.bottom, b["right"] = sp.right, b["global"] = sp.global;
                        if (j != b) {
                            matched = false;
                            break;
                        }
                    }
                }
                if (matched) {
                    param["spacing"] = j;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("set_spacing", [&](json &param) {
            Spacing sp;
            sp.top = param["spacing"]["top"], sp.left = param["spacing"]["left"], sp.bottom = param["spacing"]["bottom"], sp.right = param["spacing"]["right"], sp.global = param["spacing"]["global"];
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                comp->setSpacing(sp);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                    comp->setSpacing(sp);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_alignment", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                auto &al = comp->getAlignment();
                json j; j["horizental"] = al.horizental, j["vertical"] = al.vertical;
                param["alignment"] = j;
                param["status"] = SUCCEED;
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                json j;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                    auto &al = comp->getAlignment();
                    if (!matched) {
                        j["horizental"] = al.horizental, j["vertical"] = al.vertical;
                        matched = true;
                    } else { // 多值
                        json b; b["horizental"] = al.horizental, b["vertical"] = al.vertical;
                        if (j != b) {
                            matched = false;
                            break;
                        }
                    }
                }
                if (matched) {
                    param["alignment"] = j;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("set_alignment", [&](json &param) {
            Alignment al;
            al.horizental = param["alignment"]["horizental"], al.vertical = param["alignment"]["vertical"];
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                comp->setAlignment(al);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                    comp->setAlignment(al);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("get_html", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                param["html"] = comp->getHTML();
                param["status"] = SUCCEED;
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                bool matched = false;
                std::string html;
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                    if (!matched) html = comp->getHTML(), matched = true;
                    else if (html != comp->getHTML()) {
                        matched = false;
                        break;
                    }
                }
                if (matched) {
                    param["html"] = html;
                    param["status"] = SUCCEED;
                } else param["status"] = MULTIVL;
            });
            return param;
        });
        Register::addEvent("set_html", [&](json &param) {
            auto html = param["html"];
            // 切换器
            Register::switchBoth(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                comp->setHTML(html);
            },
            [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                for (auto cursor : cursors) {
                    auto comp = std::dynamic_pointer_cast<ComponentWritable>(cursor); // 动态类型转换
                    comp->setHTML(html);
                }
            });
            param["status"] = SUCCEED;
            return param;
        });
    }

    ComponentWritable::ComponentWritable() {
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
    }

    //// 通用虚接口
    // 非构造初始化
    void ComponentWritable::init() {
        fObj = std::make_shared<Lewzen::SVGIForeignObject>(); // 外部对象
        fObj->Width = "100%";
        fObj->Height = "100%";
        fObj->Style = "overflow: visible; pointer-events: none; user-select: none";
        fObj->Id = getId() + "_text";
        auto inner = std::make_shared<Lewzen::SVGIElement>(); // 实际外部对象
        inner->RawHTML.bind(std::bind(&ComponentWritable::getForeignHTML, this));
        fObj->add(inner);
        fObj->commit();
    }
    // 拷贝
    ComponentAbstract &ComponentWritable::operator=(const ComponentAbstract &comp) {
        auto &p = dynamic_cast<const ComponentWritable &>(comp);     
        // 拷贝可写信息
        setHTML(p._HTML);
        _spacing = p._spacing;
        _alignment = p._alignment;

        return *this;
    }
    // 序列化，并记录已操作的
    void ComponentWritable::serialize(json &j, std::vector<std::string> &processed) {
        j["html"] = _HTML;
        json jsp; jsp["top"] = _spacing.top, jsp["left"] = _spacing.left, jsp["bottom"] = _spacing.bottom, jsp["right"] = _spacing.right, jsp["global"] = _spacing.global;
        j["spacing"] = jsp;
        json jal; jal["horizental"] = _alignment.horizental, jal["vertical"] = _alignment.vertical;
        j["alignment"] = jal;
    }
    // 反序列化
    ComponentAbstract &ComponentWritable::operator=(const json &j) {
        // 反序列化可写信息
        setHTML(j["html"]);
        _spacing.top = j["spacing"]["top"], _spacing.left = j["spacing"]["left"], _spacing.bottom = j["spacing"]["bottom"], _spacing.right = j["spacing"]["right"], _spacing.global = j["spacing"]["global"];
        _alignment.horizental = j["alignment"]["horizental"], _alignment.vertical = j["alignment"]["vertical"];
        
        return *this;
    }

    //// Writable接口
    // 翻转变换后操作
    // 边缘间隔
    const ComponentWritable::Spacing ComponentWritable::getSpacing() const {
        return _spacing;
    }
    void ComponentWritable::setSpacing(const Spacing &spacing) {
        _spacing = spacing;
        onChanged();
    }
    // 对齐
    const ComponentWritable::Alignment ComponentWritable::getAlignment() const {
        return _alignment;
    }
    void ComponentWritable::setAlignment(const Alignment &alignment) {
        _alignment = alignment;
        onChanged();
    }
    // HTML内容
    const std::string ComponentWritable::getHTML() {
        return _HTML;
    }
    const std::string ComponentWritable::getForeignHTML() { // 将当前状态转化为原生HTML
        std::stringstream ss; auto rect = getWriteArea();
        ss << R"(<div xmlns="http://www.w3.org/1999/xhtml" style="width: )";
        ss << std::to_string(rect.width - _spacing.left - _spacing.right - 2 * _spacing.global) << "px"; // 上边界
        ss << "; height: ";
        ss << "1px"; // 高度
        ss << "; position:relative; top: ";
        if (_alignment.vertical == 0) ss << std::to_string(rect.y + _spacing.top + _spacing.global) << "px"; // 上准线
        else if (_alignment.vertical == 1) ss << std::to_string(rect.y + rect.height / 2) << "px"; // 居中准线
        else if (_alignment.vertical == 2) ss << std::to_string(rect.y + rect.height - _spacing.bottom - _spacing.global) << "px"; // 下准线
        ss << "; margin-left: ";
        ss << std::to_string(rect.x + _spacing.left + _spacing.global) << "px"; // 左边界
        ss << "; display: flex; align-items: unsafe ";
        if (_alignment.vertical == 0) ss << "flex-start"; // 左对齐
        else if (_alignment.vertical == 1) ss << "center"; // 居中
        else if (_alignment.vertical == 2) ss << "flex-end"; // 右对齐
        ss << "; justify-content: unsafe ";
        if (_alignment.horizental == 0) ss << "flex-start"; // 上对齐
        else if (_alignment.horizental == 1) ss << "center"; // 居中
        else if (_alignment.horizental == 2) ss << "flex-end"; // 下对齐
        ss << R"("><div style="display: inline-block; pointer-events: all">)";
        ss << _HTML;
        ss << "</div></div>";
        return ss.str();
    };
    void ComponentWritable::setHTML(const std::string &HTML) {
        _HTML = HTML;
        if (auto svgi = getSVGI().lock()) { // 非空则添加
            if (_HTML != "" && !_fObjAdded) svgi->add(fObj), _fObjAdded = true;
            else if (_HTML == "") svgi->remove(fObj), _fObjAdded = false;
        }
        onChanged();
    }    
}