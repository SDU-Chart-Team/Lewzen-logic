#ifndef __LEWZENSERVER_CIRCLE__
#define __LEWZENSERVER_CIRCLE__

#include "../comp_module/comp_rotatable.h"

namespace LewzenServer
{
    class Circle : virtual public ComponentRotatable
    {
    protected:
        // SVGI
        std::shared_ptr<Lewzen::SVGICircle> SVGICircle;
        // 关键点别名
        std::shared_ptr<CorePoint> LT, L, LB, B, RB, R, RT, T;
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

        //// 圆形接口
        virtual double getCx() const;
        virtual double getCy() const;
        virtual double getR() const;


    };
}
#endif