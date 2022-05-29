#ifndef __LEWZENSERVER_DIAMOND__
#define __LEWZENSERVER_DIAMOND__

#include "../comp/rectangle.h"

namespace LewzenServer
{
    class Diamond : virtual public Rectangle
    {
    protected:
        // SVGI
        std::shared_ptr<Lewzen::SVGIPath> SVGIPath;

    public:
        //// 通用虚接口
        // 非构造初始化
        virtual void init() override;
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;
        // 序列号，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        //// Basics虚接口
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// Diamond 接口

        const std::string getPath() const;
    };
}

#endif
