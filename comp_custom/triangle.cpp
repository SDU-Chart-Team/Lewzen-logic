#include "triangle.h"
#include "../canvas.h"

namespace LewzenServer
{
    ////
    //
    void Triangle::init()
    {

        //
        Rectangle::init();
        //
        setType("triangle");

        //
        SVGIG->children({});                // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形

        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        //
        std::function<std::string()> _getD = std::bind(&Triangle::getD, this);
        SVGIPath->D.bind(_getD);
    }
    //
    ComponentAbstract &Triangle::operator=(const ComponentAbstract &comp)
    {
        //
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Triangle &>(comp);
        return *this;
    }
    //
    void Triangle::serialize(json &j, std::vector<std::string> &processed)
    {
        //
        Rectangle::serialize(j, processed);

        //
    }
    //
    ComponentAbstract &Triangle::operator=(const json &j)
    {
        //
        Rectangle::operator=(j);

        return *this;
    }

    //// Basics
    //
    void Triangle::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); //
    }

    ////
    const std::string Triangle::getD() const
    {
        std::stringstream ss;
        ss << "M " << LT->getX() << " " << LT->getY() << " ";
        ss << "L " << R->getX() << " " << R->getY() << " ";
        ss << "L " << LB->getX() << " " << LB->getY() << " ";
        ss << "Z";

        return ss.str();
    }
}
