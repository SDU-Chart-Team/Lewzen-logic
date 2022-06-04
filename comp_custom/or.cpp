#include "or.h"
#include "../canvas.h"

namespace LewzenServer
{
    ////
    //
    void Or::init()
    {

        //
        Rectangle::init();
        //
        setType("or");

        // 维护图形SVG
        SVGIG->children({});// 移除旧的图形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        std::function<std::string()> _getD = std::bind(&Or::getD, this);
        SVGIPath->D.bind(_getD);
    }
    //
    ComponentAbstract &Or::operator=(const ComponentAbstract &comp)
    {
        //
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Or &>(comp);
        return *this;
    }
    //
    void Or::serialize(json &j, std::vector<std::string> &processed)
    {
        //
        Rectangle::serialize(j, processed);

        //
    }
    //
    ComponentAbstract &Or::operator=(const json &j)
    {
        //
        Rectangle::operator=(j);

        return *this;
    }

    //// Basics
    //
    void Or::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); //
    }

    //// Or接口
    // 计算路径
    std::string Or::getD() const
    {
        std::stringstream ss;
        ss << "M " << LT->getX() << " " << LT->getY() << " ";
        ss << "Q " << RT->getX() << " " << RT->getY() << " " << R->getX() << " " << R->getY() << " ";
        ss << "Q " << RB->getX() << " " << RB->getY() << " " << LB->getX() << " " << LB->getY() << " ";
        ss << "Z";
        return ss.str();
    }
}
