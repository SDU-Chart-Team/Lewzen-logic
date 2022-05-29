#ifndef __LEWZENSERVER_CIRCLE__
#define __LEWZENSERVER_CIRCLE__

#include "../comp/rectangle.h"

namespace LewzenServer
{
    class Circle : virtual public Rectangle
    {
    protected:
        // 实际SVGI
        std::shared_ptr<Lewzen::SVGICircle> SVGICircle;


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

        //// Basics虚接口
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// 圆形接口
        const double getCx() const;
        const double getCy() const;
        const double getR() const;


    };
}
#endif