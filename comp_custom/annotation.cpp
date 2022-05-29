#include "annotation.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Annotation::init() {


        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("annotation");
        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Annotation::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &Annotation::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Annotation &>(comp); 
    }
    // 序列化，并记录已操作的
    void Annotation::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Annotation::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);
    }
    //// Basics虚接口
    void Annotation::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
       Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

  ////Annotation interface
    const std::string Annotation::getPath() const {
        auto p0 = createPoint(getX(), getY()+getHeight()*0.5);
        auto p1 = createPoint(getX()+getWidth()*0.5, getY()+getHeight()*0.5);
        auto p2 = createPoint(getX()+getWidth()*0.5, getY());
        auto p3 = createPoint(getX()+getWidth(), getY());
        auto p4 = createPoint(getX()+getWidth()*0.5, getY()+getHeight()*0.5);
        auto p5 = createPoint(getX()+getWidth()*0.5, getY()+getHeight());
        auto p6 = createPoint(getX()+getWidth(), getY()+getHeight());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "L " << p1.get_x() << " " << p1.get_y() << " ";
        ss << "L " << p2.get_x() << " " << p2.get_y() << " ";
        ss << "L " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "M " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "L " << p5.get_x() << " " << p5.get_y() << " ";
        ss << "L " << p6.get_x() << " " << p6.get_y() << " ";
        return ss.str();

    }
}