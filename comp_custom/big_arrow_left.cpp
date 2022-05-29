#include "big_arrow_left.h"

namespace LewzenServer {
    //// 通用虚接口
    // 非构造初始化
    void BigArrowLeft::init() {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("big_arrow_left");

        // 维护图形SVG
        SVGIG->children({}); // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);
        abc = createCorePoint("abc", getX()+getWidth()*0.75, getY()+getHeight()*0.25);
        abc->setColor("orange");
                    abc->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
                        if (!corePointMoving) return;
                                    if(nx < (getX()))
                                    {
                                        abc->setX(getX());
                                    }
                                    if(nx > getX()+getWidth())
                                    {
                                        abc->setX(getX()+getWidth());
                                    }
                                    if(ny < getY())
                                    {
                                        abc->setY(getY());
                                    }
                                    if(ny > getY()+getHeight()*0.5)
                                    {
                                        abc->setY(getY()+getHeight()*0.5);
                                    }
            
                        });
                            corePoints[abc->getId()] = abc;
        cde = createCorePoint("cde", getX(), getY()+getHeight()*0.5);
        cde->setColor("orange");
                    cde->on_update([&](const double &x, const double &y, const double &nx, const double &ny) {
                        if (!corePointMoving) return;
                        if (nx < getX()) cde->setX(getX());  
                        if (nx > getX()+getWidth()) cde->setX(getX()+getWidth());
            
                        });
                            corePoints[cde->getId()] = cde;
        // 绑定图形属性
        std::function<const std::string()> _getPath = std::bind(&BigArrowLeft::getPath, this);
        SVGIPath->D.bind(_getPath);
    }    // 拷贝
    ComponentAbstract &BigArrowLeft::operator=(const ComponentAbstract &comp) {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const BigArrowLeft &>(comp); 
        // 拷贝关键点位置
        *abc = *(p.abc);
        // 拷贝关键点位置
        *cde = *(p.cde);
        return *this;
    }
    // 序列化，并记录已操作的
    void BigArrowLeft::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    // 反序列化
    ComponentAbstract &BigArrowLeft::operator=(const json &j) {
        // 父类反序列化
        Rectangle::operator=(j);
        // 注册关键点
        abc = corePoints["abc"];
        // 注册关键点
        cde = corePoints["cde"];
        return *this;
    }
    //// Basics虚接口
    void BigArrowLeft::moveCorePoint(const std::string &id, const double &dx, const double &dy) {
        double disY0 = abc->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX0 = abc->getX() - getX();
        double ptgX0 = ((abc->getX() - getX()) / getWidth()) * getWidth();
        double ptgY0 = ((abc->getY() - getY()) / getHeight()) * getHeight();
        double disY1 = cde->getY() - getY(); // 记录控制点到矩形上边的距离
        double disX1 = cde->getX() - getX();
        double ptgX1 = ((cde->getX() - getX()) / getWidth()) * getWidth();
        double ptgY1 = ((cde->getY() - getY()) / getHeight()) * getHeight();
        if (id == "abc") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *abc += createPoint(dx, dy);
            corePointMoving = false;
if(abc->getX()<cde->getX()){abc->setX(cde->getX());}        }
        else if (id == "cde") { // 移动控制点
            corePointMoving = true; // 开启更新锁
            *cde += createPoint(dx, 0);
            corePointMoving = false;
if(cde->getX()>abc->getX()){cde->setX(abc->getX());}        }
        else {
            Rectangle::moveCorePoint(id, dx, dy);
            if (getX()+ptgX0 > getX()+getWidth()) ptgX0 = getX()+getWidth()-getX();
            if (getX()+ptgX0 < getX()) ptgX0 = getX()-getX();
            if ( getY()+ptgY0 > getY()+getHeight()*0.5) ptgY0 = getY()+getHeight()*0.5-getY();
            if ( getY()+ptgY0 < getY()) ptgY0 = getY()-getY();
            *abc = createPoint(getX()+ptgX0, getY() + ptgY0); // 设置新的坐标
                        if (getX()+ptgX1 > getX()+getWidth()) ptgX1 = getX()+getWidth()-getX();
            if (getX()+ptgX1 < getX()) ptgX1 = getX()-getX();
            if ( getY()+ptgY1 > getY()+getHeight()) ptgY1 = getY()+getHeight()-getY();
            if ( getY()+ptgY1 < getY()) ptgY1 = getY()-getY();
            *cde = createPoint(getX()+ptgX1, getY() + ptgY1); // 设置新的坐标
                    }
        onChanged(); // 更新事件
    }

  ////BigArrowLeft interface
    const std::string BigArrowLeft::getPath() const {
        auto p0 = createPoint(getX(), abc->getY());
        auto p1 = createPoint(abc->getX(), abc->getY());
        auto p2 = createPoint(abc->getX(), getY());
        auto p3 = createPoint(getX()+getWidth(), getY()+getHeight()*0.5);
        auto p4 = createPoint(abc->getX(), getY()+getHeight());
        auto p5 = createPoint(abc->getX(), getY()+getHeight()-(abc->getY()-getY()));
        auto p6 = createPoint(getX(), getY()+getHeight()-(abc->getY()-getY()));
        auto p7 = createPoint(cde->getX(), cde->getY());
        auto p8 = createPoint(getX(), abc->getY());
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
        return ss.str();

    }
}