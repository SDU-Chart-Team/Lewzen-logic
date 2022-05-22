#include "and.h"
#include "../canvas.h"

namespace LewzenServer
{
        //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void And::init() {
        // 设置类型
        setType("and");

        // 父类初始化
        ComponentRotatable::init();

        // 添加图形SVG
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        
        // 初始化关键点表
        LT = createCorePoint("LT", 0, 0),
        L = createCorePoint("L", 0, 50),
        LB = createCorePoint("LB", 0, 100),
        B = createCorePoint("B", 100, 100),
        RB = createCorePoint("RB", 200, 100),
        R = createCorePoint("R", 200, 50),
        RT = createCorePoint("RT", 200, 0),
        T = createCorePoint("T", 100, 0);
        LT->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LB->setX(nx); RT->setY(ny);
            *L = (*LT + *LB) * 0.5;
            *T = (*LT + *RT) * 0.5;
        });
        LB->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LT->setX(nx); RB->setY(ny);
            *L = (*LT + *LB) * 0.5;
            *B = (*LB + *RB) * 0.5;
        });
        RB->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            RT->setX(nx); LB->setY(ny);
            *R = (*RT + *RB) * 0.5;
            *B = (*LB + *RB) * 0.5;
        });
        RT->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            RB->setX(nx); LT->setY(ny);
            *R = (*RT + *RB) * 0.5;
            *T = (*LT + *RT) * 0.5;
        });
        L->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LT->setX(nx), LB->setX(nx);
        });
        B->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LB->setY(ny), RB->setY(ny);
        });
        R->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            RT->setX(nx), RB->setX(nx);
        });
        T->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            LT->setY(ny), RT->setY(ny);
        });
        // 注册关键点
        setCorePoints({ LT, L, LB, B, RB, R, RT, T });

        // 绑定属性
        std::function<std::string()> _getD = std::bind(&And::getD, this);
        SVGIPath->D.bind(_getD);
    }
    // 拷贝
    ComponentAbstract &And::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        ComponentRotatable::operator=(comp);
        
        auto &p = dynamic_cast<const And &>(comp);        
        // 拷贝关键点位置
        *LT = *(p.LT),
        *L = *(p.L),
        *LB = *(p.LB),
        *B = *(p.B),
        *RB = *(p.RB),
        *R = *(p.R),
        *RT = *(p.RT),
        *T = *(p.T);
    }
    // 序列化，并记录已操作的
    void And::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        ComponentRotatable::serialize(j, processed);

        // (无额外私有内容)
    }
    // 反序列化
    ComponentAbstract &And::operator=(const json &j) {
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
        T = corePoints["T"];
    }

    //// Basics虚接口
    // 移动关键点
    void And::moveCorePoint(const std::string &id, const double &_dx, const double &_dy) {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(_dx, _dy)); // 计算组件坐标系的Δ
        double dx = delta.get_x(), dy = delta.get_y();
        corePointMoving = true; // 更新锁
        // 具体更新
        if (id == "L") *L += createPoint(dx, 0);
        if (id == "R") *R += createPoint(dx, 0);
        if (id == "T") *T += createPoint(0, dy);
        if (id == "B") *B += createPoint(0, dy);
        if (id == "LT") *LT += createPoint(dx, dy);
        if (id == "LB") *LB += createPoint(dx, dy);
        if (id == "RT") *RT += createPoint(dx, dy);
        if (id == "RB") *RB += createPoint(dx, dy);

        corePointMoving = false; // 更新锁
        onCorePointMoved();
        onChanged(); // 更新事件
    }

    //// 图形接口
    std::string And::getD() const {
        return "M " + std::to_string(LT->getX()) + " " +std::to_string(LT->getY()) + " " +"Q " + std::to_string(RT->getX()) + " " + std::to_string(RT->getY()) + " " + std::to_string(R->getX()) + " " + std::to_string(R->getY()) + " " + "Q " + std::to_string(RB->getX()) + " " + std::to_string(RB->getY()) + " " + std::to_string(LB->getX()) + " " + std::to_string(LB->getY()) + " " + "Q " + std::to_string(T->getX()) + " " + std::to_string(R->getY()) + " " + std::to_string(LT->getX()) + " " + std::to_string(LT->getY());

    }
}