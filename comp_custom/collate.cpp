#include "collate.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void Collate::init() {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("collate");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&Collate::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &Collate::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Collate &>(comp); 

        return *this;
    }
    // 序列化，并记录已操作的
    void Collate::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &Collate::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);

        return *this;
    }
    //// Basics虚接口
    void Collate::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
       Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

  ////Collate interface
    const std::string Collate::getPath() const {
        auto p0 = createPoint(getX()+getWidth()*0.9, getY());
        auto p1 = createPoint(getX()+getWidth(), getY());
        auto p2 = createPoint(getX()+getWidth(), getY());
        auto p3 = createPoint(getX()+getWidth()*0.85, getY()+getHeight()*0.15);
        auto p4 = createPoint(getX()+getWidth()*0.15, getY()+getHeight()*0.85);
        auto p5 = createPoint(getX(), getY()+getHeight());
        auto p6 = createPoint(getX(), getY()+getHeight());
        auto p7 = createPoint(getX()+getWidth()*0.1, getY()+getHeight());
        auto p8 = createPoint(getX()+getWidth()*0.9, getY()+getHeight());
        auto p9 = createPoint(getX()+getWidth(), getY()+getHeight());
        auto p10 = createPoint(getX()+getWidth(), getY()+getHeight());
        auto p11 = createPoint(getX()+getWidth()*0.85, getY()+getHeight()*0.85);
        auto p12 = createPoint(getX()+getWidth()*0.15, getY()+getHeight()*0.15);
        auto p13 = createPoint(getX(), getY());
        auto p14 = createPoint(getX(), getY());
        auto p15 = createPoint(getX()+getWidth()*0.1, getY());
        auto p16 = createPoint(getX()+getWidth()*0.9, getY());
        auto p17 = createPoint(getX()+getWidth()*0.9, getY());
        auto p18 = createPoint(getX()+getWidth(), getY());
        auto p19 = createPoint(getX()+getWidth(), getY());
        auto p20 = createPoint(getX()+getWidth()*0.85, getY()+getHeight()*0.15);
        auto p21 = createPoint(getX()+getWidth()*0.15, getY()+getHeight()*0.85);
        auto p22 = createPoint(getX(), getY()+getHeight());
        auto p23 = createPoint(getX(), getY()+getHeight());
        auto p24 = createPoint(getX()+getWidth()*0.1, getY()+getHeight());
        auto p25 = createPoint(getX()+getWidth()*0.9, getY()+getHeight());
        auto p26 = createPoint(getX()+getWidth(), getY()+getHeight());
        auto p27 = createPoint(getX()+getWidth(), getY()+getHeight());
        auto p28 = createPoint(getX()+getWidth()*0.85, getY()+getHeight()*0.85);
        auto p29 = createPoint(getX()+getWidth()*0.15, getY()+getHeight()*0.15);
        auto p30 = createPoint(getX(), getY());
        auto p31 = createPoint(getX(), getY());
        auto p32 = createPoint(getX()+getWidth()*0.1, getY());
        auto p33 = createPoint(getX()+getWidth()*0.9, getY());
        std::stringstream ss;
        ss << "M " << p0.get_x() << " " << p0.get_y() << " ";
        ss << "C " << p1.get_x() << " " << p1.get_y()<< " " << p2.get_x() << " " << p2.get_y() << " " << p3.get_x() << " " << p3.get_y() << " ";
        ss << "L " << p4.get_x() << " " << p4.get_y() << " ";
        ss << "C " << p5.get_x() << " " << p5.get_y()<< " " << p6.get_x() << " " << p6.get_y() << " " << p7.get_x() << " " << p7.get_y() << " ";
        ss << "L " << p8.get_x() << " " << p8.get_y() << " ";
        ss << "C " << p9.get_x() << " " << p9.get_y()<< " " << p10.get_x() << " " << p10.get_y() << " " << p11.get_x() << " " << p11.get_y() << " ";
        ss << "L " << p12.get_x() << " " << p12.get_y() << " ";
        ss << "C " << p13.get_x() << " " << p13.get_y()<< " " << p14.get_x() << " " << p14.get_y() << " " << p15.get_x() << " " << p15.get_y() << " ";
        ss << "L " << p16.get_x() << " " << p16.get_y() << " ";
        ss << "M " << p17.get_x() << " " << p17.get_y() << " ";
        ss << "C " << p18.get_x() << " " << p18.get_y()<< " " << p19.get_x() << " " << p19.get_y() << " " << p20.get_x() << " " << p20.get_y() << " ";
        ss << "L " << p21.get_x() << " " << p21.get_y() << " ";
        ss << "C " << p22.get_x() << " " << p22.get_y()<< " " << p23.get_x() << " " << p23.get_y() << " " << p24.get_x() << " " << p24.get_y() << " ";
        ss << "L " << p25.get_x() << " " << p25.get_y() << " ";
        ss << "C " << p26.get_x() << " " << p26.get_y()<< " " << p27.get_x() << " " << p27.get_y() << " " << p28.get_x() << " " << p28.get_y() << " ";
        ss << "L " << p29.get_x() << " " << p29.get_y() << " ";
        ss << "C " << p30.get_x() << " " << p30.get_y()<< " " << p31.get_x() << " " << p31.get_y() << " " << p32.get_x() << " " << p32.get_y() << " ";
        ss << "L " << p33.get_x() << " " << p33.get_y() << " ";
        return ss.str();

    }
}