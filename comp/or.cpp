#include "or.h"
#include "../canvas.h"

namespace LewzenServer
{
    ////
    //
    void Or::init()
    {
        //
        setType("or");

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
        std::function<std::string()> _getD = std::bind(&Or::getD, this);
        SVGIPath->D.bind(_getD);
    }
    //
    ComponentAbstract &Or::operator=(const ComponentAbstract &comp)
    {
        //
        ComponentRotatable::operator=(comp);

        auto &p = dynamic_cast<const Or &>(comp);
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
    void Or::serialize(json &j, std::vector<std::string> &processed)
    {
        //
        ComponentRotatable::serialize(j, processed);

        //
    }
    //
    ComponentAbstract &Or::operator=(const json &j)
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
    void Or::moveCorePoint(const std::string &id, const double &_dx, const double &_dy)
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
    std::string Or::getD() const
    {
        return "M " + std::to_string(LT->getX()) + " " + std::to_string(LT->getY()) + " " + "Q " + std::to_string(RT->getX()) + " " + std::to_string(RT->getY()) + " " + std::to_string(R->getX()) + " " + std::to_string(R->getY()) + " " + "Q " + std::to_string(RB->getX()) + " " + std::to_string(RB->getY()) + " " + std::to_string(LB->getX()) + " " + std::to_string(LB->getY()) + " Z";
    }
}
