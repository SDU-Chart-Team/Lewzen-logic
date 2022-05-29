#include "data_storage.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void DataStorage::init() {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("data_storage");

        // 维护图形SVG
        SVGIG->children({});// 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        Control = createCorePoint("Control", getX()+getWidth()*0.3, getY()+getHeight()*0.5);
        Control->setColor("orange");
        Control->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
            if (!corePointMoving) return;
            if (nx < getX()) Control->setX(getX()); // 
            if (nx > getX()+getWidth()) Control->setX(getX()+getWidth()); // 

            });
                corePoints[Control->getId()] = Control;
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&DataStorage::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &DataStorage::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const DataStorage &>(comp); 
        // 拷贝关键点位置
        *Control = *(p.Control);
        return *this;
    }
    // 序列化，并记录已操作的
    void DataStorage::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &DataStorage::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);
        // 注册关键点
        Control = corePoints["Control"];
        return *this;
    }
    //// Basics虚接口
    void DataStorage::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        double disY = Control->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX = Control->getX() - getX();
        double ptgX = ((Control->getX() - getX()) / getWidth()) * getWidth();
        double ptgY = ((Control->getY() - getY()) / getHeight()) * getHeight();
        if (id == "Control") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *Control += createPoint(dx, 0);
            corePointMoving = false;
        } else { // 移动其他点
            Rectangle::moveCorePoint(id, dx, dy);
            if (getX()+ptgX > getX()+getWidth()) ptgX = getWidth();
            if (getY()+ptgY > getY()+getHeight()) ptgY = getHeight();
            *Control = createPoint(getX()+ptgX, getY() + ptgY); // 设置新的坐标
        }
        onChanged(); // 更新事件
    }

  ////DataStorage interface
    const std::string DataStorage::getPath() const {
        auto p0 = createPoint(getX(), getY());
        auto p1 = createPoint(getX(), getY()+getHeight());
        auto p2 = createPoint(getX()+getWidth()-(Control->getX() - getX()), getY()+getHeight());
        auto p3 = createPoint(getX()+getWidth()-(Control->getX() - getX()), getY());
        auto p4 = createPoint(getX(), getY());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "A " << getX()+getWidth()*0.7 << " " << (Control->getX() - getX())<< " " << 0 << " " << 0  <<" "<< 1 << " " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "A " << getX()+getWidth()*0.7 << " " << (Control->getX() - getX())<< " " << 0 << " " << 0  <<" "<< 0 << " " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        return ss.str();

    }
}