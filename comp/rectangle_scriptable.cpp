#include "rectangle_scriptable.h"
#include <emscripten.h>

namespace LewzenServer {
    bool RectangleScriptable::registered = false;
    void RectangleScriptable::registering() {
        registered = true;
        Register::addEvent("rect_js_config", [&](json &param) {
            // 切换器
            Register::switchCursorOnly(param, module_type,
            [&](std::shared_ptr<ComponentAbstract> &cursor){
                auto comp = std::dynamic_pointer_cast<RectangleScriptable>(cursor); // 动态类型转换
                comp->init(param["config"]);
                param["status"] = SUCCEED;
            });
            return param;
        });
    }
    RectangleScriptable::RectangleScriptable() {
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
    }

    //// 通用虚接口
    // 非构造初始化
    void RectangleScriptable::init() {
        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("rectangle_scriptable");
        // 维护图形SVG
        SVGIG->children({});// 移除旧的图形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        // 绑定属性
        std::function<std::string()> _getD = std::bind(&RectangleScriptable::getPath, this);
        SVGIPath->D.bind(_getD);
    }
    void RectangleScriptable::init(json config) {
        this->config = config;
        context.clear();customCorePointNames.clear();customCallbacks.clear();customDeltas.clear();beforeRectUpdate.clear();afterRectUpdate.clear();
        if (config.contains("size")) {
            if (config["size"].contains("width") && config["size"].contains("height")) {
                double w = config["size"]["width"], h = config["size"]["height"];
                Rectangle::moveCorePoint("RB", w - getWidth(), h - getHeight());
            }
        }
        for (auto &p : config["points"]) {
            std::string pid = p["pid"];
            double pos_x = p["pos"]["x"], pos_y = p["pos"]["y"];
            auto point = createCorePoint(pid, pos_x, pos_y);
            point->setColor(p["color"]);
            customCallbacks[point->getId()] = p["callback"];
            customDeltas[point->getId()] = p["delta"];
            point->on_update([&, pid](const double &x, const double &y, const double &nx, const double &ny) {
                if (!corePointMoving) return;
                context[pid]["nx"] = nx, context[pid]["ny"] = ny;
                runScript(customCallbacks[pid]);
                context[pid].erase("nx"), context[pid].erase("ny");
            });
            corePoints[point->getId()] = point;
        }
        beforeRectUpdate = config["before_rect_change"];
        afterRectUpdate = config["after_rect_change"];
        path = config["path"];
        runScript(""); // 更新上下文
    }
    // 拷贝
    ComponentAbstract &RectangleScriptable::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);
        auto &p = dynamic_cast<const RectangleScriptable &>(comp);
        
        // 拷贝自定义信息
        SVGIG->add(SVGIPath);
        init(p.config);
        
        // 拷贝关键点位置
        for (auto wp : corePoints) *corePoints[wp.first] = *p.corePoints.at(wp.first);
        runScript(""); // 更新上下文

        return *this;
    }
    // 序列化，并记录已操作的
    void RectangleScriptable::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);

        // 序列化自定义
        j["config"] = config;
    }
    // 反序列化
    ComponentAbstract &RectangleScriptable::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        // 拷贝自定义信息
        SVGIG->add(SVGIPath);
        init(j["config"]);

        // 拷贝关键点位置
        auto &jc = j["core_points"];
        for (auto& [k, v] : jc.items()) { // json转关键点列表
            auto p = createCorePoint(k);
            p->deserialize(v);
            *corePoints[k] = *p;
        }
        runScript(""); // 更新上下文

        return *this;
    }

    void RectangleScriptable::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        runScript(beforeRectUpdate);
        bool found = false;
        if (customDeltas.count(id)) {
            corePointMoving = true; // 更新锁
            context[id]["dx"] = dx, context[id]["dy"] = dy;
            runScript(customDeltas[id]);
            if (context[id].contains("dx") && context[id].contains("dy")) *corePoints[id] += createPoint(context[id]["dx"], context[id]["dy"]);
            context[id].erase("dx"), context[id].erase("dy");
            corePointMoving = false; // 更新锁
            found = true;
        }
        if (!found) {
            Rectangle::moveCorePoint(id, dx, dy);
            runScript(afterRectUpdate); // 矩形更新后调整
        }
        onChanged(); // 更新事件
    }

    // 计算路径
    const std::string RectangleScriptable::getPath() const {
        if (path == "") return "";
        json ret = runScript(path, 1);
        if (ret.contains("path")) return ret["path"];
        return "";
    }

    // 转译
    json RectangleScriptable::runScript(std::string script) {
        // 更新上下文
        context["x"] = getX(), context["y"] = getY(), context["width"] = getWidth(), context["height"] = getHeight();
        for (auto wp : corePoints) context[wp.first]["x"] = wp.second->getX(), context[wp.first]["y"] = wp.second->getY();

        script = "(function(){let context=" + context.dump() + ";" + script + ";return JSON.stringify(context);})()";
        context = json::parse(emscripten_run_script_string(script.c_str()));

        // 上下文同步
        for (auto wp : corePoints) *corePoints[wp.first] = createPoint(context[wp.first]["x"], context[wp.first]["y"]);
        return context;
    }

    json RectangleScriptable::runScript(std::string script, bool) const {
        if (script == "") return context;

        // 更新上下文
        json context = this->context;
        context["x"] = getX(), context["y"] = getY(), context["width"] = getWidth(), context["height"] = getHeight();
        for (auto wp : corePoints) context[wp.first]["x"] = wp.second->getX(), context[wp.first]["y"] = wp.second->getY();

        script = "(function(){let context=" + context.dump() + ";" + script + ";return JSON.stringify(context);})()";
        context = json::parse(emscripten_run_script_string(script.c_str()));
        return context;
    }
}