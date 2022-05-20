//
// Created by l'l on 2022/5/16.
//

#ifndef WEBSOCKETSERVER_LINE_H
#define WEBSOCKETSERVER_LINE_H

#include "../comp_module.h"
#include <map>
#include <set>
namespace LewzenServer{
    class Line : virtual public ComponentRotatable,
                 virtual public ComponentScalable,
                 virtual public ComponentFlippable,
                 virtual public ComponentStylized {

    private:
        static bool registered;
        const std::string module_type = "Line";

    protected:

        // 注册接口
        void registering();
        // SVGI
        std::shared_ptr<Lewzen::SVGIPath> SVGILine;
        std::shared_ptr<Lewzen::SVGIPath> SVGICurve;
        std::shared_ptr<Lewzen::SVGIPath> SVGIVerticalLine;
        std::shared_ptr<Lewzen::SVGIPath> SVGIHorizontalLine;

        // 关键点序列,顺序
        std::vector< std::shared_ptr<CorePoint> >pointList;

        //线条起点
        std::shared_ptr<CorePoint> startPoint;
        //线条终点
        std::shared_ptr<CorePoint> endPoint;

        std::shared_ptr<CorePoint> midPoint;

        std::string startArrow = "null",endArrow="null";

        std::string straightLine = "straight_line";
        std::string verticalLine = "vertical_line";
        std::string curve = "curve";
        std::string horizontalLine = "horizontal_line";


        std::map<std::string, std::shared_ptr<Lewzen::SVGIMarker>>arrows;

    protected:
        std::shared_ptr<Lewzen::SVGIMarker> end_arrow;
        std::shared_ptr<Lewzen::SVGIMarker> start_arrow;
        std::shared_ptr<Lewzen::SVGIPath> arrowPath;

        std::shared_ptr<Lewzen::SVGIMarker> start_arrow_circle;
        std::shared_ptr<Lewzen::SVGIMarker> end_arrow_circle;

        int ndSize = 0;


    public:

        Line();
        //// 通用虚接口
        // 非构造初始化
        virtual void init() override;
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        virtual Lewzen::Point2D getRotateCenter() const;


        //// Basics虚接口
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// Scalable接口
        virtual void scale(const double &scaleX, const double &scaleY) override;

        //// Flippable接口
        virtual void flip(const double &a, const double &b, const double &c) override;

        //// 线条接口
        const CorePoint &getStartPoint() const;

        int setLineType(std::string lineType);

        void setStartPoint(const CorePoint &startPoint);

        const CorePoint &getEndPoint() const;

        void setEndPoint(const CorePoint &endPoint);

        std::string getD();

        void initArrow();

        const std::string &getStartArrow() const;

        virtual void setStartArrow(const std::string &startArrow);

        const std::string &getEndArrow() const;

        virtual void setEndArrow(const std::string &endArrow);

        std::string getCurveD();
        std::string getVerticalLineD();
        std::string getHorizontalLineD();

    };
}



#endif //WEBSOCKETSERVER_LINE_H
