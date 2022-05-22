#include "star.h"
#include "../canvas.h"

namespace LewzenServer
{
    ////
    //
    void Star::init()
    {
        //
        setType("star");

        //
        ComponentRotatable::init();

        //
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

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

        //
        std::function<std::string()> _getD = std::bind(&Star::getD, this);
        SVGIPath->D.bind(_getD);
    }
    //
    ComponentAbstract &Star::operator=(const ComponentAbstract &comp)
    {
        //
        ComponentRotatable::operator=(comp);

        auto &p = dynamic_cast<const Star &>(comp);
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
    void Star::serialize(json &j, std::vector<std::string> &processed)
    {
        //
        ComponentRotatable::serialize(j, processed);

        //
    }
    //
    ComponentAbstract &Star::operator=(const json &j)
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
    void Star::moveCorePoint(const std::string &id, const double &_dx, const double &_dy)
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

        corePointMoving = false; //
        onCorePointMoved();
        onChanged(); //
    }

    ////
    std::string Star::getD() const
    {
        double x1 = 0.6 * (L->getX()) + 0.4 * (R->getX());
        double x2 = 0.4 * (L->getX()) + 0.6 * (R->getX());
        double x3 = 0.3 * (L->getX()) + 0.7 * (R->getX());
        double x4 = 0.7 * (L->getX()) + 0.3 * (R->getX());
        double x5 = 0.2 * (L->getX()) + 0.8 * (R->getX());
        double x6 = 0.8 * (L->getX()) + 0.2 * (R->getX());
        double y1 = 0.7 * (T->getY()) + 0.3 * (B->getY());
        double y2 = 0.4 * (T->getY()) + 0.6 * (B->getY());
        double y3 = 0.2 * (T->getY()) + 0.8 * (B->getY());
        return "M " + std::to_string(T->getX()) + " " + std::to_string(T->getY()) + " " + "L " + std::to_string(x2) + " " + std::to_string(y1) + " " + "L " + std::to_string(R->getX()) + " " + std::to_string(y1) + " " + "L " + std::to_string(x3) + " " + std::to_string(y2) + " " + "L " + std::to_string(x5) + " " + std::to_string(B->getY()) + " " + "L " + std::to_string(B->getX()) + " " + std::to_string(y3) + " " + "L " + std::to_string(x6) + " " + std::to_string(B->getY()) + " " + "L " + std::to_string(x4) + " " + std::to_string(y2) + " " + "L " + std::to_string(L->getX()) + " " + std::to_string(y1) + " " + "L " + std::to_string(x1) + " " + std::to_string(y1) + " Z";
    }
}
