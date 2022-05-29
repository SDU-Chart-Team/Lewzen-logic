#include "register.h"
#include "canvas.h"

namespace LewzenServer {
    // 单组件游标
    bool Register::selected = false;
    std::weak_ptr<ComponentAbstract> Register::cursor = std::shared_ptr<ComponentAbstract>(nullptr);
    // 返回合法选中的组件，否则为Null
    std::shared_ptr<ComponentAbstract> Register::selected_with(const std::string &module) {
        if (auto c = cursor.lock()) if (module == "" || c->moduleContains(module)) return c;
        return std::shared_ptr<ComponentAbstract>(nullptr);
    }
    // 多组件游标
    bool Register::multi_selected = false;
    std::vector<std::weak_ptr<ComponentAbstract>> Register::cursors = {};
    // 返回合法选中的组件，若无则空
    std::vector<std::shared_ptr<ComponentAbstract>> Register::multi_selected_with(const std::string &module) {
        std::vector<std::shared_ptr<ComponentAbstract>> vec;
        for (auto &wp : cursors) if (auto c = wp.lock()) if (module == "" || c->moduleContains(module)) vec.push_back(c);
        return std::move(vec);
    }

    std::map<std::string, std::function<const json(json &)>> Register::events = {};
    // 注册命令
    void Register::registering() {
        // 将组件集合转为Id列表串
        addEvent("add", [&](json &param){ // 添加组件
            std::string type = param["type"];
            Canvas::add(type);
            param["status"] = SUCCEED;
            std::vector<std::string> ids, tops;
            Canvas::getAddedComponents(ids, tops);
            param["ids"] = ids;
            param["tops"] = tops;
            return param;
        });
        addEvent("cursor", [&](json &param){ // 选中单组件
            std::string id = param["id"];
            if (auto comp = Canvas::cursor(id).lock()) { // 选中单组件
                cursor = comp;
                selected = true; multi_selected = false; // 更新标记
                cursors.clear();
                param["id"] = id;
                param["status"] = SUCCEED;
                return param;
            }
            run(R"({"command": "uncursor"})"); // 取消选中
            param["status"] = NULLPTR;
            return param;
        });
        addEvent("cursors", [&](json &param){ // 选中多组件
            std::vector<std::string> ids = param["ids"];        
            cursors = std::move(Canvas::cursors(ids));
            if (cursors.size() == 0) { // 空指针
                run(R"({"command": "uncursor"})"); // 取消选中
                param["status"] = NULLPTR;
                return param;
            }
            multi_selected = true; selected = false; // 更新标记
            cursor = std::shared_ptr<LewzenServer::ComponentAbstract>(nullptr);
            param["ids"] = ids;
            param["status"] = SUCCEED;
            return param;
        });
        addEvent("uncursor", [&](json &param){ // 取消选中
            selected = multi_selected = false;
            cursor = std::shared_ptr<LewzenServer::ComponentAbstract>(nullptr);
            cursors.clear();
            return SUCCEED;
        });
        addEvent("remove", [&](json &param){ // 删除组件
            int time = param["time"];
            Canvas::remove(time);
            param["status"] = SUCCEED;
            std::vector<std::string> ids;
            Canvas::getRemovedComponents(ids);
            param["ids"] = ids;
            return param;
        });
        addEvent("copy", [&](json &param){ // 复制组件
            Canvas::copy();
            param["status"] = SUCCEED;
            std::vector<std::string> ids, tops;
            Canvas::getAddedComponents(ids, tops);
            param["ids"] = ids;
            param["tops"] = tops;
            return param;
        });
        addEvent("readd", [&](json &param){ // 重添加组件
            Canvas::readd();
            param["status"] = SUCCEED;
            std::vector<std::string> ids, tops;
            Canvas::getAddedComponents(ids, tops);
            param["ids"] = ids;
            param["tops"] = tops;
            return param;
        });
        addEvent("discard", [&](json &param){ // 丢弃组件
            int time = param["time"];
            if (Canvas::discard(time)) param["status"] = SUCCEED;
            else param["status"] = IFAILED;
            return param;
        });
        addEvent("save", [&](json &param){ // 序列化
            param["json"] = Canvas::serialize();
            param["status"] = SUCCEED;
            return param;
        });
        addEvent("load", [&](json &param){ // 反序列化
            Canvas::deserialize(param["json"]);

            param["status"] = SUCCEED;
            std::vector<std::string> ids, tops;
            Canvas::getAddedComponents(ids, tops);
            param["ids"] = ids;
            param["tops"] = tops;

            return param;
        });
    }

    // 初始化
    const std::string Register::init() {
        auto HTML = Canvas::init();
        registering();
        return HTML;
    }
    
    // 添加命令
    void Register::addEvent(const std::string &interface_name,
        std::function<const json(json &)> interface_body) {
        events[interface_name] = interface_body;
    }
    // 运行命令
    const std::string Register::run(const std::string &cmd) {
        std::function<void(json &, json &)> run_cmd = [](json &in, json &out) {
            std::string cname = in["command"];
            try {
                if (!events.count(cname)) {
                    in["status"] = NULLCMD;
                    out.push_back(in);
                } else {
                    out.push_back(events[cname](in));
                }
            } catch (const std::exception& e) { // 无法处理的异常
                in["error"] = "unhandled exception";
                in["error_msg"] = e.what();
                out.push_back(in);
            }
        };
        auto _in = json::parse(cmd);
        json _out; json _ret;
        if (_in.is_array()) { // 执行每条
            for (auto _i : _in) run_cmd(_i, _out);
        } else if (_in.is_object()) { // 执行一条
            run_cmd(_in, _out);
        }
        _ret["returns"] = _out;
        _ret["domcmd"] = Canvas::commit(); // 更新
        return _ret.dump();
    }

    // 切换器，仅认可单选
    void Register::switchCursorOnly(json &j, const std::string &module_type,
        std::function<void(std::shared_ptr<ComponentAbstract> &)> doSomething) {
        if (!selected) { // 未选中
            j["status"] = NTARGET;
            return;
        }
        auto c = selected_with(module_type);
        if (!c) { // 检查注册
            j["status"] = NULLREG;
            return;
        }
        doSomething(c);
    }
    // 切换器，仅认可多选
    void Register::switchMultiCursorOnly(json &j, const std::string &module_type,
        std::function<void(std::vector<std::shared_ptr<ComponentAbstract>> &)> doSomething) {
        if (!multi_selected) { // 未选中
            j["status"] = NTARGET;
            return;
        }
        auto vec = multi_selected_with(module_type);
        if (vec.size() == 0) { // 检查注册
            j["status"] = NULLREG;
            return;
        }
        doSomething(vec);
    }
    // 切换器
    void Register::switchBoth(json &j, const std::string &module_type,
        std::function<void(std::shared_ptr<ComponentAbstract> &)> doSomethingA,
        std::function<void(std::vector<std::shared_ptr<ComponentAbstract>> &)> doSomethingB) {
        if (selected) { // 选中单个
            if (!selected) { // 未选中
                j["status"] = NTARGET;
                return;
            }
            auto c = selected_with(module_type);
            if (!c) { // 检查注册
                j["status"] = NULLREG;
                return;
            }
            doSomethingA(c);
        } else if (multi_selected) { // 选中多个
            if (!multi_selected) { // 未选中
                j["status"] = NTARGET;
                return;
            }
            auto vec = multi_selected_with(module_type);
            if (vec.size() == 0) { // 检查注册
                j["status"] = NULLREG;
                return;
            }
            doSomethingB(vec);
        } else j["status"] = NTARGET; // 未选中
    }

    // 实用方法
    void Register::listComponentId(json &j, const std::vector<std::weak_ptr<ComponentAbstract>> &list) {
        for (auto &p : list) {
            if (auto pp = p.lock()) {
                j.push_back(pp->getId());
            }
        }
    };
    void Register::listComponentId(json &j, const std::set<std::shared_ptr<ComponentAbstract>> &set) {
        for (auto &p : set) {
            j.push_back(p->getId());
        }
    };
}