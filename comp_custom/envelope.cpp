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

        // 绑定属性
        // std::function<double()> _getX = std::bind(&Envelope::getX, this);
        // std::function<double()> _getY = std::bind(&Envelope::getY, this);
        // std::function<double()> _getWidth = std::bind(&Envelope::getWidth, this);
        // std::function<double()> _getHeight = std::bind(&Envelope::getHeight, this);
        // SVGIRect->X.bind(_getX);
        // SVGIRect->Y.bind(_getY);
        // SVGIRect->Width.bind(_getWidth);
        // SVGIRect->Height.bind(_getHeight);
        std::function<std::string()> _getD = std::bind(&Envelope::getD, this);
        SVGIPath->D.bind(_getD);
    }
    //
    ComponentAbstract &Envelope::operator=(const ComponentAbstract &comp)
    {
        //
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Envelope &>(comp);
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
