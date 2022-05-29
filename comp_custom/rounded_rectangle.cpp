#include "rounded_rectangle.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void RoundedRectangle::init()
    {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("rounded_rectangle");

        // 无需添加图形SVG

        // 初始化关键点表
        Control = createCorePoint("Control", 190, 25);
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                            {
                                double maxR = std::min((this->getHeight() / 2), (this->getWidth() / 2));
                                if (!corePointMoving) return;
                                if(nx > R->getX())
                                {
                                    Control->setX(R->getX());
                                }
                                if(nx < R->getX() - maxR)
                                {
                                    Control->setX(R->getX() - maxR);
                                }
                            });
        // 注册关键点
        corePoints[Control->getId()] = Control;

        // 绑定属性
        std::function<double()> _getRx = std::bind(&RoundedRectangle::getRx, this);
        std::function<double()> _getRy = std::bind(&RoundedRectangle::getRy, this);

        SVGIRect->Rx.bind(_getRx);
        SVGIRect->Ry.bind(_getRy);
    }
    // 拷贝
    ComponentAbstract &RoundedRectangle::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const RoundedRectangle &>(comp);
        // 拷贝关键点位置
        *Control = *(p.Control);
    }
    // 序列化，并记录已操作的
    void RoundedRectangle::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        Rectangle::serialize(j, processed);

        // (无额外私有内容)
    }
    // 反序列化
    ComponentAbstract &RoundedRectangle::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        Control = corePoints["Control"];
    }

    //// Basics虚接口
    // 移动关键点
    void RoundedRectangle::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        // 圆角半径=控制点到右侧的距离
        double d = R->getX() - Control->getX();
        double maxR = std::min((this->getHeight() / 2), (this->getWidth() / 2));

        if (id == "Control")
        {
            corePointMoving = true; // 开启更新锁
            *Control += createPoint(dx, 0); // 只允许纵向移动
            corePointMoving = false;
        }
        else
        {
            Rectangle::moveCorePoint(id, dx, dy);
            if(d > maxR)
            {
                d = maxR;
            }
            if(d < 0)
            {
                d = 0;
            }
            *Control = createPoint(R->getX() - d, getY() + getHeight() / 4);
        }
        onChanged(); // 更新事件
    }

    //// 矩形接口
    const double RoundedRectangle::getRx() const
    {
        return std::abs(R->getX() - Control->getX());
    }
    const double RoundedRectangle::getRy() const
    {
        return std::abs(R->getX() - Control->getX());
    }
}