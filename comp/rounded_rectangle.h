#ifndef __LEWZENSERVER_ROUNDEDRECTANGLE__
#define __LEWZENSERVER_ROUNDEDRECTANGLE__

#include "../comp_module/comp_rotatable.h"

namespace LewzenServer
{
    class RoundedRectangle : virtual public ComponentRotatable
    {
    protected:
        // SVGI
        std::shared_ptr<Lewzen::SVGIRect> SVGIRect;
        // 关键点别名
        std::shared_ptr<CorePoint> LT, L, LB, B, RB, R, RT, T, I;
        // 标记
        bool corePointMoving = false;

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

        //// 矩形接口
        virtual double getX() const;
        virtual double getY() const;
        virtual double getWidth() const;
        virtual double getHeight() const;
        virtual double getRx() const;
        virtual double getRy() const;
    };
}
#endif