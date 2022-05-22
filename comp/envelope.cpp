#include "envelope.h"
#include "../canvas.h"

namespace LewzenServer
{
    ////
    //
    void Envelope::init()
    {
        //
        setType("envelope");

        //
        ComponentRotatable::init();

        //
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIRect = std::make_shared<Lewzen::SVGIRect>();
        SVGIG->add(SVGIPath);
        SVGIG->add(SVGIRect);

        //
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
        //
        setCorePoints({LT, L, LB, B, RB, R, RT, T});

        // 绑定属性
        std::function<double()> _getX = std::bind(&Envelope::getX, this);
        std::function<double()> _getY = std::bind(&Envelope::getY, this);
        std::function<double()> _getWidth = std::bind(&Envelope::getWidth, this);
        std::function<double()> _getHeight = std::bind(&Envelope::getHeight, this);
        SVGIRect->X.bind(_getX);
        SVGIRect->Y.bind(_getY);
        SVGIRect->Width.bind(_getWidth);
        SVGIRect->Height.bind(_getHeight);
        std::function<std::string()> _getD = std::bind(&Envelope::getD, this);
        SVGIPath->D.bind(_getD);
    }
    //
    ComponentAbstract &Envelope::operator=(const ComponentAbstract &comp)
    {
        //
        ComponentRotatable::operator=(comp);

        auto &p = dynamic_cast<const Envelope &>(comp);
        //
        *LT = *(p.LT),
        *L = *(p.L),
        *LB = *(p.LB),
        *B = *(p.B),
        *RB = *(p.RB),
        *R = *(p.R),
        *RT = *(p.RT),
        *T = *(p.T);
    }
    //
    void Envelope::serialize(json &j, std::vector<std::string> &processed)
    {
        //
        ComponentRotatable::serialize(j, processed);

        //
    }
    //
    ComponentAbstract &Envelope::operator=(const json &j)
    {
        //
        ComponentRotatable::operator=(j);

        //
        LT = corePoints["LT"],
        L = corePoints["L"],
        LB = corePoints["LB"],
        B = corePoints["B"],
        RB = corePoints["RB"],
        R = corePoints["R"],
        RT = corePoints["RT"],
        T = corePoints["T"];
    }

    //// Basics
    //
    void Envelope::moveCorePoint(const std::string &id, const double &_dx, const double &_dy)
    {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(_dx, _dy)); //
        double dx = delta.get_x(), dy = delta.get_y();
        corePointMoving = true; //
        //
        if (id == "L")
            *L += createPoint(dx, 0);
        if (id == "R")
            *R += createPoint(dx, 0);
        if (id == "T")
            *T += createPoint(0, dy);
        if (id == "B")
            *B += createPoint(0, dy);
        if (id == "LT")
            *LT += createPoint(dx, dy);
        if (id == "LB")
            *LB += createPoint(dx, dy);
        if (id == "RT")
            *RT += createPoint(dx, dy);
        if (id == "RB")
            *RB += createPoint(dx, dy);

        corePointMoving = false;
        onCorePointMoved();
        onChanged();
    }

    //// 矩形接口
    double Envelope::getX() const
    {
        return std::min(L->getX(), R->getX());
    }
    double Envelope::getY() const
    {
        return std::min(T->getY(), B->getY());
    }
    double Envelope::getWidth() const
    {
        return std::abs(L->getX() - R->getX());
    }
    double Envelope::getHeight() const
    {
        return std::abs(T->getY() - B->getY());
    }
    ////
    std::string Envelope::getD() const
    {
        return "M " + std::to_string(LT->getX()) + " " + std::to_string(LT->getY()) + " L " + std::to_string(T->getX()) + " " + std::to_string(R->getY()) + " L " + std::to_string(RT->getX()) + " " + std::to_string(RT->getY());
    }
}
