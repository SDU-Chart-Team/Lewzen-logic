
#ifndef __LEWZENSERVER_ENVELOPE__
#define __LEWZENSERVER_ENVELOPE__

#include "../comp/rectangle.h"

namespace LewzenServer
{
    class Envelope : virtual public Rectangle
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
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        //// Basics
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        // Evenlope接口
        // 计算路径
        const std::string getD() const;
    };
}

#endif
