#include "circle.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void Circle::init()
    {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("circle");

        //// 添加图形SVG
        // delete rect of Rectangle
        SVGIG->children({}); 
        Rectangle::moveCorePoint("RB", -100, 0);
        SVGICircle = std::make_shared<Lewzen::SVGICircle>();
        SVGIG->add(SVGICircle);

        //// 由于圆形关键点移动规则与矩形不同，需要重写
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
                        if (!corePointMoving)
                        {
                            return;
                        }
                        LT->setX(nx);
                        RB->setY(ny);
                        *L = (*LT + *LB) * 0.5;
                        *B = (*LB + *RB) * 0.5; 
                    });
        RB->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if(!corePointMoving)
                        {
                            return;
                        }
                        RT->setX(nx); 
                        LB->setY(ny);
                        *R = (*RT + *RB) * 0.5;
                        *B = (*LB + *RB) * 0.5; 
                    });
        RT->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if (!corePointMoving)
                        {
                            return;
                        }
                        RB->setX(nx);
                        LT->setY(ny);
                        *R = (*RT + *RB) * 0.5;
                        *T = (*LT + *RT) * 0.5; 
                    });

        R->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if (!corePointMoving)
                        {
                            return;
                        }
                        double dx = nx - x;
                        double dy = ny - y;
                        RT->setX(nx);
                        // *RB += createPoint(dx, dy * 2);
                        *RB = (*R) * 2 - *RT; 
                    });
        B->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if (!corePointMoving)
                        {
                            return;
                        }
                        double dx = nx - x;
                        double dy = ny - y;
                        LB->setY(ny);
                        // *RB += createPoint(dx * 2, dy);
                        *RB = (*R) * 2 - (*LB); 
                    });
        L->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if (!corePointMoving)
                        {
                            return;
                        }
                        double dx = nx - x;
                        double dy = ny - y;
                        LT->setX(nx);
                        // *LB += createPoint(dx, dy * 2);
                        *LB = (*L) * 2 - (*LT); 
                    });
        T->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if (!corePointMoving)
                        {
                            return;
                        }
                        double dx = nx - x;
                        double dy = ny - y;
                        LT->setY(ny);
                        // *RT += createPoint(dx * 2, dy);
                        *RT = (*T) * 2 - (*LT); 
                    });

        // 绑定图形属性
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
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Circle &>(comp);
        return *this;
    }

    // 序列化
    void Circle::serialize(json &j, std::vector<std::string> &processed)
    {
        // parent
        Rectangle::serialize(j, processed);
    }

    // 反序列化
    ComponentAbstract &Circle::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);
        return *this;
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
        // onCorePointMoved();
        onChanged();
    }

    //// 圆形接口
    const double Circle::getCx() const
    {
        return T->getX();
    }
    const double Circle::getCy() const
    {
        return L->getY();
    }
    const double Circle::getR() const
    {
        return std::abs((L->getX() - R->getX()) * 0.5);
    }
}