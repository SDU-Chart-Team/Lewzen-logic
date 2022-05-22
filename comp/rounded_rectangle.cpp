#include "rounded_rectangle.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void RoundedRectangle::init()
    {
        // 设置类型
        setType("rounded_rectangle");

        // 父类初始化
        ComponentRotatable::init();

        // 添加图形SVG
        SVGIRect = std::make_shared<Lewzen::SVGIRect>();
        SVGIG->add(SVGIRect);

        // 初始化关键点表
        LT = createCorePoint("LT", 0, 0),
        L = createCorePoint("L", 0, 50),
        LB = createCorePoint("LB", 0, 100),
        B = createCorePoint("B", 100, 100),
        RB = createCorePoint("RB", 200, 100),
        R = createCorePoint("R", 200, 50),
        RT = createCorePoint("RT", 200, 0),
        T = createCorePoint("T", 100, 0);
        I = createCorePoint("I", 190, 25);
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
        // 注册关键点
        setCorePoints({LT, L, LB, B, RB, R, RT, T, I});

        // 绑定属性
        std::function<double()> _getX = std::bind(&RoundedRectangle::getX, this);
        std::function<double()> _getY = std::bind(&RoundedRectangle::getY, this);
        std::function<double()> _getWidth = std::bind(&RoundedRectangle::getWidth, this);
        std::function<double()> _getHeight = std::bind(&RoundedRectangle::getHeight, this);
        std::function<double()> _getRx = std::bind(&RoundedRectangle::getRx, this);
        std::function<double()> _getRy = std::bind(&RoundedRectangle::getRy, this);
        SVGIRect->X.bind(_getX);
        SVGIRect->Y.bind(_getY);
        SVGIRect->Width.bind(_getWidth);
        SVGIRect->Height.bind(_getHeight);
        SVGIRect->Rx.bind(_getRx);
        SVGIRect->Ry.bind(_getRy);
    }
    // 拷贝
    ComponentAbstract &RoundedRectangle::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        ComponentRotatable::operator=(comp);

        auto &p = dynamic_cast<const RoundedRectangle &>(comp);
        // 拷贝关键点位置
        *LT = *(p.LT),
        *L = *(p.L),
        *LB = *(p.LB),
        *B = *(p.B),
        *RB = *(p.RB),
        *R = *(p.R),
        *RT = *(p.RT),
        *T = *(p.T);
        *I = *(p.I);
    }
    // 序列化，并记录已操作的
    void RoundedRectangle::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        ComponentRotatable::serialize(j, processed);

        // (无额外私有内容)
    }
    // 反序列化
    ComponentAbstract &RoundedRectangle::operator=(const json &j)
    {
        // 父类反序列化
        ComponentRotatable::operator=(j);

        // 注册关键点
        LT = corePoints["LT"],
        L = corePoints["L"],
        LB = corePoints["LB"],
        B = corePoints["B"],
        RB = corePoints["RB"],
        R = corePoints["R"],
        RT = corePoints["RT"],
        T = corePoints["T"],
        I = corePoints["I"];
    }

    //// Basics虚接口
    // 移动关键点
    void RoundedRectangle::moveCorePoint(const std::string &id, const double &_dx, const double &_dy)
    {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(_dx, _dy)); // 计算组件坐标系的Δ
        double dx = delta.get_x(), dy = delta.get_y();
        corePointMoving = true; // 更新锁
        // 具体更新
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
        if (id == "I")
        {
            // TODO
            double x0 = I->getX();
            double x2 = x0 + dx;
            double maxR = std::min((this->getHeight() / 2), (this->getWidth() / 2));
            if (x2 <= R->getX() && x2 >= (R->getX() - maxR))
            {
                *I += createPoint(dx, 0);
            }
            else if (x2 > R->getX())
            {
                I->setX(R->getX());
            }
            else
            {
                I->setX(std::abs(R->getX() - maxR));
            }
        }

        corePointMoving = false; // 更新锁
        onCorePointMoved();
        onChanged(); // 更新事件
    }

    //// 矩形接口
    double RoundedRectangle::getX() const
    {
        return std::min(L->getX(), R->getX());
    }
    double RoundedRectangle::getY() const
    {
        return std::min(T->getY(), B->getY());
    }
    double RoundedRectangle::getWidth() const
    {
        return std::abs(L->getX() - R->getX());
    }
    double RoundedRectangle::getHeight() const
    {
        return std::abs(T->getY() - B->getY());
    }
    double RoundedRectangle::getRx() const
    {
        return std::abs(R->getX() - I->getX());
    }
    double RoundedRectangle::getRy() const
    {
        return std::abs(R->getX() - I->getX());
    }
}