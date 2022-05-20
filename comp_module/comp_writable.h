#ifndef __LEWZENSERVER_COMP_WRITABLE__
#define __LEWZENSERVER_COMP_WRITABLE__
#include "comp_abstract.h"
#include "../release/lewzen-core/core.h"

namespace LewzenServer {
    class ComponentWritable : virtual public ComponentAbstract {
    private:
        static bool registered;
        const std::string module_type = "Writable";
    protected:
        // 注册接口
        void registering();
        // 外部物体
        std::shared_ptr<Lewzen::SVGIForeignObject> fObj;
        // HTML
        std::string _HTML;
        bool _fObjAdded;
    public:
        ComponentWritable();

        //// 通用虚接口
        // 非构造初始化
        virtual void init();
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp);
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed);
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j);

        //// Writable接口
        // 区域，其中(x, y)均为画布坐标
        struct WriteArea {
            double x = 0, y = 0, width = 0, height = 0;
        };
        virtual const WriteArea getWriteArea() = 0;
        // 边缘间隔
        struct Spacing {
            double top = 0, left = 0, bottom = 0, right = 0;
            double global = 10;
        };
    protected:
        Spacing _spacing;
    public:
        const Spacing getSpacing() const;
        void setSpacing(const Spacing &spacing);
        // 对齐
        struct Alignment {
            int horizental = 1;
            int vertical = 1;
        };
    protected:
        Alignment _alignment;
    public:
        const Alignment getAlignment() const;
        void setAlignment(const Alignment &alignment);
        // HTML内容
        const std::string getHTML();
        const std::string getForeignHTML();
        void setHTML(const std::string &HTML);
    };
}
#endif