#include "circle.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void Circle::init()
    {
        // 设置类型
        setType("circle");

        // 父类初始化
        ComponentRotatable::init();

        // 添加图形SVG
        SVGICircle = std::make_shared<Lewzen::SVGICircle>();
        SVGIG->add(SVGICircle);

        // 初始化关键点表
        LT = createCorePoint("LT", 0, 0);
        L = createCorePoint("L", 0, 50),
        LB = createCorePoint("LB", 0, 100),
        B = createCorePoint("B", 50, 100),
        RB = createCorePoint("RB", 100, 100),
        R = createCorePoint("R", 100, 50),
        RT = createCorePoint("RT", 100, 0),
        T = createCorePoint("T", 50, 0);
        // 从动规律：R=RB;B=RB;L=LB;T=RT'
        // 更新函数，在set坐标和+=操作时都调用回调函数
        LT->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if(!corePointMoving)
                            {return;}
                        LB->setX(nx); 
                        RT->setY(ny);
                        *L = (*LT + *LB) * 0.5;
                        *T = (*LT + *RT) * 0.5;
                    });
        LB->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if(!corePointMoving)
                            {return;}
                        LT->setX(nx);
                        RB->setY(ny);
                        *L = (*LT + *LB) * 0.5;
                        *B = (*LB + *RB) * 0.5;
                        
                    });
        RB->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if(!corePointMoving)
                            {return;}
                        RT->setX(nx); 
                        LB->setY(ny);
                        *R = (*RT + *RB) * 0.5;
                        *B = (*LB + *RB) * 0.5;
                    });
        RT->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if(!corePointMoving)
                            {return;}
                        RB->setX(nx); 
                        LT->setY(ny);
                        *R = (*RT + *RB) * 0.5;
                        *T = (*LT + *RT) * 0.5;

                    });

        R->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if (!corePointMoving)
                            {return;}
                        double dx = nx - x;
                        double dy = ny - y;
                        RT->setX(nx);
                        // *RB += createPoint(dx, dy * 2);
                        *RB = (*R) * 2 - *RT;
                        // LB->setY(RB->getX());
                        // *T = (*LT + *RT) * 0.5;
                        // *L = (*LT + *LB) * 0.5;
                        // *B = (*LB + *RB) * 0.5; 
                    });
        B->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if (!corePointMoving)
                            {return;} 
                        double dx = nx - x;
                        double dy = ny - y;
                        LB->setY(ny);
                        // *RB += createPoint(dx * 2, dy);
                        *RB = (*R) * 2 - (*LB);
                        // RT->setX(RB->getX());
                        // *R = (*RT + *RB) * 0.5;
                        // *T = (*LT + *RT) * 0.5;
                        // *L = (*LT + *LB) * 0.5;
                    });
        L->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if(!corePointMoving)
                            {return;}
                        double dx = nx - x;
                        double dy = ny - y;
                        LT->setX(nx);
                        // *LB += createPoint(dx, dy * 2);
                        *LB = (*L) * 2 - (*LT);
                        // RB->setY(LB->getY());
                        // *R = (*RT + *RB) * 0.5;
                        // *T = (*LT + *RT) * 0.5;
                        // *B = (*LB + *RB) * 0.5; 
                    });
        T->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if(!corePointMoving)
                            {return;}
                        double dx = nx - x;
                        double dy = ny - y;
                        LT->setY(ny);
                        // *RT += createPoint(dx * 2, dy);
                        *RT = (*T) * 2 - (*LT);
                        // RB->setX(RT->getX());
                        // *R = (*RT + *RB) * 0.5;
                        // *L = (*LT + *LB) * 0.5;
                        // *B = (*LB + *RB) * 0.5; 
                    });
        // 注册关键点
        setCorePoints({LT, L, LB, B, RB, R, RT, T});

        std::function<double()> _getCx = std::bind(&Circle::getCx, this);
        std::function<double()> _getCy = std::bind(&Circle::getCy, this);
        std::function<const double()> _getR = std::bind(&Circle::getR, this);
        SVGICircle->Cx.bind(_getCx);
        SVGICircle->Cy.bind(_getCy);
        SVGICircle->R.bind(_getR);
    }

    // copy
    ComponentAbstract &Circle::operator=(const ComponentAbstract &comp)
    {
        ComponentRotatable::operator=(comp);

        auto &p = dynamic_cast<const Circle &>(comp);
        // copy key points
        *LT = *(p.LT),
        *L = *(p.L),
        *LB = *(p.LB),
        *B = *(p.B),
        *RB = *(p.RB),
        *R = *(p.R),
        *RT = *(p.RT),
        *T = *(p.T);
    }

    // 序列化
    void Circle::serialize(json &j, std::vector<std::string> &processed)
    {
        // parent
        ComponentRotatable::serialize(j, processed);
    }

    // 反序列化
    ComponentAbstract &Circle::operator=(const json &j)
    {
        // 父类反序列化
        ComponentRotatable::operator=(j);

        // register key points
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
    // move
    // 为保证圆形，dx恒等于dy；且移动非角点时，存在从动点
    // 角点的决定性移动方向：LT:dx;RT:dy;RB:dy;LB=dx

    void Circle::moveCorePoint(const std::string &id, const double &_dx, const double &_dy)
    {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(_dx, _dy));
        double dx = delta.get_x(), dy = delta.get_y();
        corePointMoving = true;
        if (id == "L")
        {
            *L += createPoint(dx, dx * (-0.5));
        }
        if (id == "R")
        {
            *R += createPoint(dx, dx * 0.5);
        }
        if (id == "T")
        {
            *T += createPoint(dy * (-0.5), dy);
        }
        if (id == "B")
        {
            *B += createPoint(dy * 0.5, dy);
        }
        if (id == "LT")
        {
            *LT += createPoint(dx, dx);
        }
        if (id == "LB")
        {
            *LB += createPoint(dx, dx);
        }
        if (id == "RT")
        {
            *RT += createPoint(dy, dy);
        }
        if (id == "RB")
        {
            *RB += createPoint(dy, dy);
        }

        corePointMoving = false;
        onCorePointMoved();
        onChanged();
    }

    //// 圆形接口
    double Circle::getCx() const
    {
        return T->getX();
    }
    double Circle::getCy() const
    {
        return L->getY();
    }
    double Circle::getR() const
    {
        return std::abs((L->getX() - R->getX()) * 0.5);
    }
}