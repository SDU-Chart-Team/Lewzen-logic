#include "stored_data.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void StoredData::init() {
            // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("stored_data");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&StoredData::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &StoredData::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const StoredData &>(comp); 
        return *this;
    }
    // 序列化，并记录已操作的
    void StoredData::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &StoredData::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);
        return *this;
    }
    //// Basics虚接口
    void StoredData::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
       Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

  ////StoredData interface
    const std::string StoredData::getPath() const {
        auto p0 = createPoint(getX()+getWidth()*0.15, getY());
        auto p1 = createPoint(getX()+getWidth()*0.15, getY()+getHeight());
        auto p2 = createPoint(getX()+getWidth(), getY()+getHeight());
        auto p3 = createPoint(getX()+getWidth(), getY());
        auto p4 = createPoint(getX()+getWidth()*0.15, getY());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "A " << getWidth()*0.15 << " " << getHeight()*0.5<< " " << 0 << " " << 0  <<" "<< 0 << " " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "A " << getWidth()*0.15 << " " << getHeight()*0.5<< " " << 0 << " " << 0  <<" "<< 1 << " " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        return ss.str();

    }
}