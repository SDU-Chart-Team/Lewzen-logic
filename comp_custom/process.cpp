#include "process.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void Process::init()
    {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("process");

        // 添加图形SVG
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 初始化关键点表
        Control = createCorePoint("Control", 25, 25);

        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny)
                           {
                        if (!corePointMoving) return; 
                        if(nx > getX() + getWidth() / 2)
                        {
                            Control -> setX(T->getX());
                        }
                        if(nx < getX())
                        {
                            Control ->setX(getX());
                        } });
        // 注册关键点
        corePoints[Control->getId()] = Control;

        // 绑定属性
        std::function<std::string()> _getD = std::bind(&Process::getPath, this);
        SVGIPath->D.bind(_getD);
    }
    // 拷贝
    ComponentAbstract &Process::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Process &>(comp);
        // 拷贝关键点位置

        *Control = *(p.Control);
    }
    // 序列化，并记录已操作的
    void Process::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        Rectangle::serialize(j, processed);

        // (无额外私有内容)
    }
    // 反序列化
    ComponentAbstract &Process::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);

        // 注册关键点
        Control = corePoints["Control"];
    }

    //// Basics虚接口
    // 移动关键点
    void Process::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        double d = Control->getX() - getX();
        // 具体更新
        if (id == "I")
        {
            corePointMoving = true; // 更新锁
            *Control += createPoint(dx, 0);
            corePointMoving = false; // 更新锁
        }
        else
        {
            Rectangle::moveCorePoint(id, dx, dy);
            if (d > getWidth() / 2)
            {
                d = getWidth() / 2;
            }
            *Control = createPoint(getX() + d, getY() + getHeight() / 4);
        }

        onChanged(); // 更新事件
    }

    //// Process接口

    const std::string Process::getPath() const
    {
        double x2 = (T->getX()) * 2 - Control->getX();

        std::stringstream ss;
        ss << "M " << Control->getX() << " " << T->getY() << " ";
        ss << "L " << Control->getX() << " " << B->getY() << " ";
        ss << "M " << x2 << " " << T->getY() << " ";
        ss << "L " << x2 << " " << B->getY() << " ";
        return ss.str();
    }
}