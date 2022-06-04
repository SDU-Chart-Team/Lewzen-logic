#include "envelope.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void Envelope::init()
    {

        //
        Rectangle::init();
        // 设置类型
        setType("envelope");

        // 维护图形SVG
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        std::function<std::string()> _getD = std::bind(&Envelope::getD, this);
        SVGIPath->D.bind(_getD);
    }
    //
    ComponentAbstract &Envelope::operator=(const ComponentAbstract &comp)
    {
        //
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Envelope &>(comp);
        return *this;
    }
    //
    void Envelope::serialize(json &j, std::vector<std::string> &processed)
    {
        //
        Rectangle::serialize(j, processed);

        //
    }
    //
    ComponentAbstract &Envelope::operator=(const json &j)
    {
        //
        Rectangle::operator=(j);
        return *this;

    }

    //// Basics
    //
    void Envelope::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged();
    }

    //// 计算路径
    const std::string Envelope::getD() const
    {
        std::stringstream ss;
        ss << "M " << LT->getX() << " " << LT->getY() << " ";
        ss << "L " << T->getX() << " " << R->getY() << " ";
        ss << "L " << RT->getX() << " " << RT->getY() << " ";
        ss << "Z ";

        return ss.str();
    }
}
