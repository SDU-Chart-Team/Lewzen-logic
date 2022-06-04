#include "use_case.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    //
    void UseCase::init()
    {

        Rectangle::init();
        setType("use_case");

        // 维护图形SVG
        SVGIG->children({});// 移除旧的图形
        SVGIEllipse = std::make_shared<Lewzen::SVGIEllipse>();
        SVGIG->add(SVGIEllipse);

        //绑定属性
        std::function<double()> _getCx = std::bind(&UseCase::getCx, this);
        std::function<double()> _getCy = std::bind(&UseCase::getCy, this);
        std::function<double()> _getRx = std::bind(&UseCase::getRx, this);
        std::function<double()> _getRy = std::bind(&UseCase::getRy, this);
        SVGIEllipse->Cx.bind(_getCx);
        SVGIEllipse->Cy.bind(_getCy);
        SVGIEllipse->Rx.bind(_getRx);
        SVGIEllipse->Ry.bind(_getRy);
    }

    // copy
    ComponentAbstract &UseCase::operator=(const ComponentAbstract &comp)
    {
        Rectangle::operator=(comp);


        auto &p = dynamic_cast<const UseCase &>(comp);
        return *this;
    }

    // serialization
    void UseCase::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列号
        Rectangle::serialize(j, processed);

        // 无额外私有内容
    }

    // 反序列化
    ComponentAbstract &UseCase::operator=(const json &j)
    {
        Rectangle::operator=(j);

        return *this;
    }

    //// Basics虚接口
    // 移动关键点
    void UseCase::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged();
    }

    //// 椭圆形接口
    const double UseCase::getCx() const
    {
        return (L->getX() + R->getX()) * 0.5;
    }
    const double UseCase::getCy() const
    {
        return (T->getY() + B->getY()) * 0.5;
    }
    const double UseCase::getRx() const
    {
        return std::abs(L->getX() - R->getX()) * 0.5;
    }
    const double UseCase::getRy() const
    {
        return std::abs(T->getY() - B->getY()) * 0.5;
    }
}