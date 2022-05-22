#include "ellipse.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    //
    void Ellipse::init()
    {
        setType("ellipse");

        ComponentRotatable::init();

        //
        SVGIEllipse = std::make_shared<Lewzen::SVGIEllipse>();
        SVGIG->add(SVGIEllipse);

        // 初始化关键点表
        LT = createCorePoint("LT", 0, 0),
        L = createCorePoint("L", 0, 50),
        LB = createCorePoint("LB", 0, 100),
        B = createCorePoint("B", 100, 100),
        RB = createCorePoint("RB", 200, 100),
        R = createCorePoint("R", 200, 50),
        RT = createCorePoint("RT", 200, 0),
        T = createCorePoint("T", 100, 0);
        LT->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                      {
            if (!corePointMoving) return;
            LB->setX(nx); RT->setY(ny);
            *L = (*LT + *LB) * 0.5;
            *T = (*LT + *RT) * 0.5; });
        LB->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                      {
            if (!corePointMoving) return;
            LT->setX(nx); RB->setY(ny);
            *L = (*LT + *LB) * 0.5;
            *B = (*LB + *RB) * 0.5; });
        RB->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                      {
            if (!corePointMoving) return;
            RT->setX(nx); LB->setY(ny);
            *R = (*RT + *RB) * 0.5;
            *B = (*LB + *RB) * 0.5; });
        RT->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                      {
            if (!corePointMoving) return;
            RB->setX(nx); LT->setY(ny);
            *R = (*RT + *RB) * 0.5;
            *T = (*LT + *RT) * 0.5; });
        L->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                     {
            if (!corePointMoving) return;
            LT->setX(nx), LB->setX(nx); });
        B->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                     {
            if (!corePointMoving) return;
            LB->setY(ny), RB->setY(ny); });
        R->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                     {
            if (!corePointMoving) return;
            RT->setX(nx), RB->setX(nx); });
        T->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                     {
            if (!corePointMoving) return;
            LT->setY(ny), RT->setY(ny); });
        // Register key points
        setCorePoints({LT, L, LB, B, RB, R, RT, T});

        //绑定属性
        std::function<double()> _getCx = std::bind(&Ellipse::getCx, this);
        std::function<double()> _getCy = std::bind(&Ellipse::getCy, this);
        std::function<double()> _getRx = std::bind(&Ellipse::getRx, this);
        std::function<double()> _getRy = std::bind(&Ellipse::getRy, this);
        SVGIEllipse->Cx.bind(_getCx);
        SVGIEllipse->Cy.bind(_getCy);
        SVGIEllipse->Rx.bind(_getRx);
        SVGIEllipse->Ry.bind(_getRy);
    }

    // copy
    ComponentAbstract &Ellipse::operator=(const ComponentAbstract &comp)
    {
        ComponentRotatable::operator=(comp);

        auto &p = dynamic_cast<const Ellipse &>(comp);
        // key points positions
        *LT = *(p.LT),
        *L = *(p.L),
        *LB = *(p.LB),
        *B = *(p.B),
        *RB = *(p.RB),
        *R = *(p.R),
        *RT = *(p.RT),
        *T = *(p.T);
    }

    // serialization
    void Ellipse::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列号
        ComponentRotatable::serialize(j, processed);

        // 无额外私有内容
    }

    // 反序列化
    ComponentAbstract &Ellipse::operator=(const json &j)
    {
        ComponentRotatable::operator=(j);

        // 注册关键点
        LT = corePoints["LT"],
        L = corePoints["L"],
        LB = corePoints["LB"],
        B = corePoints["B"],
        RB = corePoints["RB"],
        R = corePoints["R"],
        RT = corePoints["RT"],
        T = corePoints["T"];
    }

    //// Basics虚接口
    // 移动关键点
    void Ellipse::moveCorePoint(const std::string &id, const double &_dx, const double &_dy)
    {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(_dx, _dy)); // 计算组件坐标系的Δ
        double dx = delta.get_x(), dy = delta.get_y();
        corePointMoving = true;
        // update
        if (id == "L")
        {
            *L += createPoint(dx, 0);
        }
        if (id == "R")
        {
            *R += createPoint(dx, 0);
        }
        if (id == "T")
        {
            *T += createPoint(0, dy);
        }
        if (id == "B")
        {
            *B += createPoint(0, dy);
        }
        if (id == "LT")
        {
            *LT += createPoint(dx, dy);
        }
        if (id == "LB")
        {
            *LB += createPoint(dx, dy);
        }
        if (id == "RT")
        {
            *RT += createPoint(dx, dy);
        }
        if (id == "RB")
        {
            *RB += createPoint(dx, dy);
        }

        corePointMoving = false;
        onCorePointMoved();
        onChanged();
    }

    //// 椭圆形接口
    double
    Ellipse::getCx() const
    {
        return (L->getX() + R->getX()) * 0.5;
    }
    double Ellipse::getCy() const
    {
        return (T->getY() + B->getY()) * 0.5;
    }
    double Ellipse::getRx() const
    {
        return std::abs(L->getX() - R->getX()) * 0.5;
    }
    double Ellipse::getRy() const
    {
        return std::abs(T->getY() - B->getY()) * 0.5;
    }
}