#include "internal_storage.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void InternalStorage::init()
    {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("internal_storage");

        // 添加图形SVG
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点
        Control = createCorePoint("Control", 25, 25);
        Control->setColor("orange");
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                    {
                        if (!corePointMoving) 
                        {
                            return;
                        }; 
                        if(nx > (getX() + getWidth()))
                        {
                            Control->setX(R->getX());
                        }
                        if(nx < getX())
                        {
                            Control->setX(getX());
                        }
                        if(ny > (getY() + getHeight()))
                        {
                            Control->setY(B->getY());
                        }
                        if(ny < getY())
                        {
                            Control->setY(getY());
                        }
                    });
        // 注册关键点
        corePoints[Control->getId()] = Control;

        // 绑定属性
        // std::function<double()> _getX = std::bind(&InternalStorage::getX, this);
        // std::function<double()> _getY = std::bind(&InternalStorage::getY, this);
        // std::function<double()> _getWidth = std::bind(&InternalStorage::getWidth, this);
        // std::function<double()> _getHeight = std::bind(&InternalStorage::getHeight, this);
        // SVGIRect->X.bind(_getX);
        // SVGIRect->Y.bind(_getY);
        // SVGIRect->Width.bind(_getWidth);
        // SVGIRect->Height.bind(_getHeight);
        std::function<std::string()> _getD = std::bind(&InternalStorage::getD, this);
        SVGIPath->D.bind(_getD);
    }
    // 拷贝
    ComponentAbstract &InternalStorage::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const InternalStorage &>(comp);
        // 拷贝关键点位置

        *Control = *(p.Control);
    }
    // 序列化，并记录已操作的
    void InternalStorage::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        Rectangle::serialize(j, processed);

        // (无额外私有内容)
    }
    // 反序列化
    ComponentAbstract &InternalStorage::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点

        Control = corePoints["Control"];
    }

    //// Basics虚接口
    // 移动关键点
    void InternalStorage::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        // 记录控制点到矩形左侧的距离
        double x0 = Control->getX() - getX();
        double y0 = Control->getY() - getY();
        // 具体更新
        if (id == "Control")
        {
            corePointMoving = true; // 更新锁
            *Control += createPoint(dx, dy);
            corePointMoving = false; // 更新锁
        }
        else
        {
            Rectangle::moveCorePoint(id, dx, dy);
            // 更新控制点
            if(x0 > getWidth())
            {
                x0 = getWidth();
            }
            if(y0 > getHeight())
            {
                y0 = getHeight();
            }
            *Control = createPoint(getX() + x0, getY() + y0);
        }

        onChanged(); // 更新事件
    }

    //// InternalStorage接口

    const std::string InternalStorage::getD() const
    {
        std::stringstream ss;
        ss << "M " << L->getX() << " " << Control->getY() << " ";
        ss << "L " << R->getX() << " " << Control-> getY() << " ";
        ss << "M " << Control->getX() << " " << T->getY() << " ";
        ss << "L " << Control->getX() << " " << B->getY() << " ";

        return ss.str();
    }
}