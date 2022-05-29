#include "cross.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void Cross::init()
    {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("cross");

        // 维护图形SVG
        SVGIG->children({});                 // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        Control0 = createCorePoint("Control0", getX() + getWidth() * 0.4, getY() + getHeight() * 0.4);
        Control0->setColor("orange");
        Control0->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                            {
                                if (!corePointMoving)
                                    return;
                                if (nx < (getX()))
                                {
                                    Control0->setX(getX());
                                }
                                if (nx > getX() + getWidth() * 0.5)
                                {
                                    Control0->setX(getX() + getWidth() * 0.5);
                                }
                                if (ny < getY())
                                {
                                    Control0->setY(getY());
                                }
                                if (ny > getY() + getHeight() * 0.5)
                                {
                                    Control0->setY(getY() + getHeight() * 0.5);
                                }
                            });
        corePoints[Control0->getId()] = Control0;
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Cross::getPath, this);
        SVGIPath->D.bind(_getPath);
    } // 拷贝
    ComponentAbstract &Cross::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Cross &>(comp);
        // 拷贝关键点位置
        *Control0 = *(p.Control0);
    }
    // 序列化，并记录已操作的
    void Cross::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Cross::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);
        // 注册关键点
        Control0 = corePoints["Control0"];
    }
    //// Basics虚接口
    void Cross::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        double disY0 = Control0->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX0 = Control0->getX() - getX();
        double ptgX0 = ((Control0->getX() - getX()) / getWidth()) * getWidth();
        double ptgY0 = ((Control0->getY() - getY()) / getHeight()) * getHeight();
        if (id == "Control0")
        {                           // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control0 += createPoint(dx, 0);
            *Control0 += createPoint(0, dy);
            corePointMoving = false;
        }
        else
        {
            Rectangle::moveCorePoint(id, dx, dy);
            if (getX() + ptgX0 > getX() + getWidth())
                ptgX0 = getWidth();
            if (getY() + ptgY0 > getY() + getHeight())
                ptgY0 = getHeight();
            *Control0 = createPoint(getX() + ptgX0, getY() + ptgY0); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

    ////Cross interface
    const std::string Cross::getPath() const
    {
        auto p0 = createPoint(Control0->getX(), Control0->getY());
        auto p1 = createPoint(Control0->getX(), getY());
        auto p2 = createPoint(getX() + getWidth() - (Control0->getX() - getX()), getY());
        auto p3 = createPoint(getX() + getWidth() - (Control0->getX() - getX()), Control0->getY());
        auto p4 = createPoint(getX() + getWidth(), Control0->getY());
        auto p5 = createPoint(getX() + getWidth(), getY() + getHeight() - (Control0->getY() - getY()));
        auto p6 = createPoint(getX() + getWidth() - (Control0->getX() - getX()), getY() + getHeight() - (Control0->getY() - getY()));
        auto p7 = createPoint(getX() + getWidth() - (Control0->getX() - getX()), getY() + getHeight());
        auto p8 = createPoint(Control0->getX(), getY() + getHeight());
        auto p9 = createPoint(Control0->getX(), getY() + getHeight() - (Control0->getY() - getY()));
        auto p10 = createPoint(getX(), getY() + getHeight() - (Control0->getY() - getY()));
        auto p11 = createPoint(getX(), Control0->getY());
        auto p12 = createPoint(Control0->getX(), Control0->getY());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "L " << p5.get_x() << " " << p5.get_y() << " ";
        ss << "L " << p6.get_x() << " " << p6.get_y() << " ";
        ss << "L " << p7.get_x() << " " << p7.get_y() << " ";
        ss << "L " << p8.get_x() << " " << p8.get_y() << " ";
        ss << "L " << p9.get_x() << " " << p9.get_y() << " ";
        ss << "L " << p10.get_x() << " " << p10.get_y() << " ";
        ss << "L " << p11.get_x() << " " << p11.get_y() << " ";
        ss << "L " << p12.get_x() << " " << p12.get_y() << " ";
        return ss.str();
    }
}