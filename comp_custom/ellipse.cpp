#include "ellipse.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    //
    void Ellipse::init()
    {

        Rectangle::init();
        setType("ellipse");

        // 维护图形SVG
        SVGIG->children({});// 移除旧的图形
        SVGIEllipse = std::make_shared<Lewzen::SVGIEllipse>();
        SVGIG->add(SVGIEllipse);

        //绑定属性
        std::function<double()> _getCx = std::bind(&Ellipse::getCx, this);
        std::function<double()> _getCy = std::bind(&Ellipse::getCy, this);
        std::function<double()> _getRx = std::bind(&Ellipse::getRx, this);
        std::function<double()> _getRy = std::bind(&Ellipse::getRy, this);
        SVGIEllipse->Cx.bind(_getCx);
        SVGIEllipse->Cy.bind(_getCy);
        SVGIEllipse->Rx.bind(_getRx);
        SVGIEllipse->Ry.bind(_getRy);
    }

    // copy
    ComponentAbstract &Ellipse::operator=(const ComponentAbstract &comp)
    {
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Ellipse &>(comp);
        return *this;
    }

    // serialization
    void Ellipse::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列号
        Rectangle::serialize(j, processed);

        // 无额外私有内容
    }

    // 反序列化
    ComponentAbstract &Ellipse::operator=(const json &j)
    {
        Rectangle::operator=(j);
        return *this;
    }

    //// Basics虚接口
    // 移动关键点
    void Ellipse::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged();
    }

    //// 椭圆形接口
    const double Ellipse::getCx() const
    {
        return (L->getX() + R->getX()) * 0.5;
    }
    const double Ellipse::getCy() const
    {
        return (T->getY() + B->getY()) * 0.5;
    }
    const double Ellipse::getRx() const
    {
        return std::abs(L->getX() - R->getX()) * 0.5;
    }
    const double Ellipse::getRy() const
    {
        return std::abs(T->getY() - B->getY()) * 0.5;
    }
}