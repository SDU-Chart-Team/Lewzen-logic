#include "star.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void Star::init()
    {

        //
        Rectangle::init();
        //
        setType("star");

        //
        SVGIG->children({});                // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 绑定图形属性
        std::function<std::string()> _getD = std::bind(&Star::getD, this);
        SVGIPath->D.bind(_getD);
    }
    //
    ComponentAbstract &Star::operator=(const ComponentAbstract &comp)
    {
        //
        Rectangle::operator=(comp);
        return *this;
    }
    //
    void Star::serialize(json &j, std::vector<std::string> &processed)
    {
        //
        Rectangle::serialize(j, processed);

        //
    }
    //
    ComponentAbstract &Star::operator=(const json &j)
    {
        //
        Rectangle::operator=(j);
        return *this;
    }

    //// Basics
    //
    void Star::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); //
    }

    //// Star接口
    const std::string Star::getD() const
    {
        double x1 = 0.6 * (L->getX()) + 0.4 * (R->getX());
        double x2 = 0.4 * (L->getX()) + 0.6 * (R->getX());
        double x3 = 0.3 * (L->getX()) + 0.7 * (R->getX());
        double x4 = 0.7 * (L->getX()) + 0.3 * (R->getX());
        double x5 = 0.2 * (L->getX()) + 0.8 * (R->getX());
        double x6 = 0.8 * (L->getX()) + 0.2 * (R->getX());
        double y1 = 0.6 * (T->getY()) + 0.4 * (B->getY());
        double y2 = 0.4 * (T->getY()) + 0.6 * (B->getY());
        double y3 = 0.2 * (T->getY()) + 0.8 * (B->getY());

        // 内部点
        auto tl = createPoint(x1, y1);
        auto tr = createPoint(x2, y1);
        auto bl = createPoint(x4, y2);
        auto br = createPoint(x3, y2);
        auto b = createPoint(B->getX(), y3);
        // 角点
        // t=T
        auto l = createPoint(L->getX(), y1);
        auto r = createPoint(R->getX(), y1);
        auto bbl = createPoint(x6, B->getY());
        auto bbr = createPoint(x5, B->getY());

        std::stringstream ss;
        ss << "M " << T->getX() << " " << T->getY() << " ";
        ss << "L " << tr.get_x() << " " << tr.get_y() << " ";
        ss << "L " << r.get_x() << " " << r.get_y() << " ";
        ss << "L " << br.get_x() << " " << br.get_y() << " ";
        ss << "L " << bbr.get_x() << " " << bbr.get_y() << " ";
        ss << "L " << b.get_x() << " " << b.get_y() << " ";
        ss << "L " << bbl.get_x() << " " << bbl.get_y() << " ";
        ss << "L " << bl.get_x() << " " << bl.get_y() << " ";
        ss << "L " << l.get_x() << " " << l.get_y() << " ";
        ss << "L " << tl.get_x() << " " << tl.get_y() << " ";
        ss << "Z";
         return ss.str();
    }
}
