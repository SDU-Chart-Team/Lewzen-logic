#ifndef __LEWZENSERVER_RECT_SCRIPT__
#define __LEWZENSERVER_RECT_SCRIPT__

#include "rectangle.h"

namespace LewzenServer {
    class RectangleScriptable : virtual public Rectangle {
    private:
        static bool registered;
        const std::string module_type = "RectangleScriptable";
    protected:
        void registering();
    public:
        RectangleScriptable();

    protected:
        json config;
        std::vector<std::string> customCorePointNames;
        std::map<std::string, std::string> customCallbacks;
        std::map<std::string, std::string> customDeltas;
        std::string beforeRectUpdate;
        std::string afterRectUpdate;
        std::string path;
        std::shared_ptr<Lewzen::SVGIPath> SVGIPath;
        json context;

        public:
        //// 通用虚接口
        // 非构造初始化
        virtual void init() override;
        void init(json config);
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        // 移动关键点
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        // 计算路径
        const std::string getPath() const;

        // 转译
        json runScript(std::string script);
        json runScript(std::string script, bool) const;
    };
}
#endif