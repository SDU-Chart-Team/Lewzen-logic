#include "manual_operation.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void ManualOperation::init() {
            // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("manual_operation");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        Control = createCorePoint("Control", getX()+getWidth()*0.2, getY()+getHeight());
        Control->setColor("orange");
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if (nx < getX()) Control->setX(getX());  
            if (nx > getX()+getWidth()*0.5) Control->setX(getX()+getWidth()*0.5);
        });
        corePoints[Control->getId()] = Control;
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&ManualOperation::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &ManualOperation::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);


        auto &p = dynamic_cast<const ManualOperation &>(comp); 
        // 拷贝关键点位置
        *Control = *(p.Control);
        return *this;
    }
    // 序列化，并记录已操作的
    void ManualOperation::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &ManualOperation::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);
        // 注册关键点
        Control = corePoints["Control"];

        
        return *this;
    }
    //// Basics虚接口
    void ManualOperation::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        double disY0 = Control->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX0 = Control->getX() - getX();
        if (id == "Control") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control += createPoint(dx, 0);
            corePointMoving = false;
        }
        else {
            Rectangle::moveCorePoint(id, dx, dy);
            if (getX()+disX0 > getX()+getWidth()*0.5) disX0 = getX()+getWidth()*0.5-getX();
            *Control = createPoint(getX()+disX0, getY()+getHeight()); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

  ////ManualOperation interface
    const std::string ManualOperation::getPath() const {
        auto p0 = createPoint(getX(), getY());
        auto p1 = createPoint(getX()+(Control->getX()-getX()), getY()+getHeight());
        auto p2 = createPoint(getX()+getWidth()-(Control->getX()-getX()), getY()+getHeight());
        auto p3 = createPoint(getX()+getWidth(), getY());
        auto p4 = createPoint(getX(), getY());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        return ss.str();

    }
}