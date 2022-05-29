#include "card.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Card::init() {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("card");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        Control = createCorePoint("Control", getX()+getWidth()*0.25, getY()+getHeight()*0.25);
        Control->setColor("orange");
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
                double maxD = std::min(getX()+getWidth()*0.5,getY()+getHeight()*0.5);
                                if(nx > maxD)
                                {
                                    Control->setX(maxD);
                                }
                                if(nx < getX())
                                {
                                    Control->setX(getX());
                                }
                                if(ny > maxD)
                                {
                                    Control->setY(maxD);
                                }
                                if(ny < getY())
                                {
                                    Control->setY(getY());
                                }
        });
                corePoints[Control->getId()] = Control;
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Card::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &Card::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Card &>(comp); 
        // 拷贝关键点位置
        *Control = *(p.Control);
    }
    // 序列化，并记录已操作的
    void Card::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Card::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);
        // 注册关键点
        Control = corePoints["Control"];
    }
    //// Basics虚接口
    void Card::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        double disY = Control->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX = Control->getX() - getX();
        if (id == "Control") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control += createPoint(dx, dx);
            corePointMoving = false; // 开启更新锁
        } else { // 移动其他点
            Rectangle::moveCorePoint(id, dx, dy);
            if (getX()+disX > getX()+getWidth()*0.5) disX = getWidth()*0.5;
            if ( getY()+disY > getY()+getHeight()*0.5) disY =getHeight()*0.5;
            *Control = createPoint(getX()+disX, getY() + disY); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

  ////Card interface
    const std::string Card::getPath() const {
        auto p0 = createPoint(getX()+getWidth(), getY());
        auto p1 = createPoint(getX()+getWidth(), getY()+getHeight());
        auto p2 = createPoint(getX(), getY()+getHeight());
        auto p3 = createPoint(getX(), getY()+(Control->getY() - getY())*2);
        auto p4 = createPoint(getX()+(Control->getX() - getX())*2, getY());
        auto p5 = createPoint(getX()+getWidth(), getY());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "L " << p5.get_x() << " " << p5.get_y() << " ";
        return ss.str();

    }
}