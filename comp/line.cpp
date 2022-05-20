//
// Created by l'l on 2022/5/16.
//

#include "line.h"
#include "../canvas.h"

namespace LewzenServer {

    //// 注册
    bool Line::registered = false;

    void Line::registering() {
        registered = true;
        Register::addEvent("get_start", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
//                                     double x = comp->getX(), y = comp->getY(), width = comp->getWidth(), height = comp->getHeight();
                                     auto startP = comp->getStartPoint();
                                     json j; j["x"] = startP.getX(), j["y"] = startP.getY();
                                     param["start"] = j;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     bool matched = false;
                                     json j;
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto startP = comp->getStartPoint();
                                         if (!matched) {
                                             j["x"] = startP.getX(), j["y"] = startP.getY();
                                             matched = true;
                                         } else { // 多值
                                             json b; b["x"] = startP.getX(), b["y"] = startP.getY();
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["start"] = j;
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });

        Register::addEvent("get_end", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
//                                     double x = comp->getX(), y = comp->getY(), width = comp->getWidth(), height = comp->getHeight();

                                     auto endP = comp->getEndPoint();
                                     json j; j["x"] = endP.getX(), j["y"] = endP.getY();
                                     param["end"] = j;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     bool matched = false;
                                     json j;
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto endP = comp->getEndPoint();
                                         if (!matched) {
                                             j["x"] = endP.getX(), j["y"] = endP.getY();
                                             matched = true;
                                         } else { // 多值
                                             json b; b["x"] = endP.getX(), b["y"] = endP.getY();
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["end"] = j;
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });
        Register::addEvent("set_start", [&](json &param) {
            double x = param["x"], y = param["y"];
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     // 计算两点的移动距离
                                     auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->startPoint));
                                     // 移动两点
                                     comp->moveCorePoint("start", p1.get_x(), p1.get_y());
//
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         // 计算两点的移动距离
                                         auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->startPoint));
//                                         auto p2 = comp->vectorToCanvas(comp->createPoint(x + width, y + height) - *(comp->RB));
                                         // 移动两点
                                         comp->moveCorePoint("start", p1.get_x(), p1.get_y());
//                                         comp->moveCorePoint("RB", p2.get_x(), p2.get_y());
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

        Register::addEvent("set_end", [&](json &param) {
            double x = param["x"], y = param["y"];
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     // 计算两点的移动距离
                                     auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->endPoint));
                                     // 移动两点
                                     comp->moveCorePoint("end", p1.get_x(), p1.get_y());
//
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         // 计算两点的移动距离
                                         auto p1 = comp->vectorToCanvas(comp->createPoint(x, y) - *(comp->endPoint));
//                                         auto p2 = comp->vectorToCanvas(comp->createPoint(x + width, y + height) - *(comp->RB));
                                         // 移动两点
                                         comp->moveCorePoint("end", p1.get_x(), p1.get_y());
//                                         comp->moveCorePoint("RB", p2.get_x(), p2.get_y());
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

        Register::addEvent("get_start_arrow", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     auto startA = comp->getStartArrow();

                                     param["start_arrow"] = startA;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     bool matched = false;
                                     json j;
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto startA = comp->getStartArrow();
                                         if (!matched) {
                                             j["start_arrow"] = startA;
                                             matched = true;
                                         } else { // 多值
                                             json b; b["start_arrow"] = startA;
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["start_arrow"] = j["start_arrow"];
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });

        Register::addEvent("get_end_arrow", [&](json &param) {
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     auto endA = comp->getEndArrow();

                                     param["end_arrow"] = endA;
                                     param["status"] = SUCCEED;
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     bool matched = false;
                                     json j;
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         auto endA = comp->getEndArrow();
                                         if (!matched) {
                                             j["end_arrow"] = endA;
                                             matched = true;
                                         } else { // 多值
                                             json b; b["end_arrow"] = endA;
                                             if (j != b) {
                                                 matched = false;
                                                 break;
                                             }
                                         }
                                     }
                                     if (matched) {
                                         param["end_arrow"] = j["end_arrow"];
                                         param["status"] = SUCCEED;
                                     } else param["status"] = MULTIVL;
                                 });
            return param;
        });

        Register::addEvent("set_start_arrow", [&](json &param) {
            auto ar = param["start_arrow"];
            // 切换器
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     comp->setStartArrow(ar);
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->setStartArrow(ar);
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

        Register::addEvent("set_end_arrow", [&](json &param) {
            auto ar = param["end_arrow"];
            // 切换器
            //std::cout<<"ar "<<ar<<std::endl;
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     //std::cout<<"ar \n";
                                     comp->setEndArrow(ar);
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->setEndArrow(ar);
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });
        Register::addEvent("set_line_type", [&](json &param) {
            auto lt = param["line_type"];
            // 切换器
            //std::cout<<"lt "<<lt<<std::endl;
            Register::switchBoth(param, module_type,
                                 [&](std::shared_ptr<ComponentAbstract> &cursor){
                                     auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                     //std::cout<<"lt \n";
                                     comp->setLineType(lt);
                                 },
                                 [&](std::vector<std::shared_ptr<ComponentAbstract>> &cursors){
                                     for (auto cursor : cursors) {
                                         auto comp = std::dynamic_pointer_cast<Line>(cursor); // 动态类型转换
                                         comp->setLineType(lt);
                                     }
                                 });
            param["status"] = SUCCEED;
            return param;
        });

    }

    Line::Line() {
        //std::cout<<"line()\n";
        if (!registered) registering(); // 注册
        addModuleTypes(module_type); // 添加模块类型
        initArrow();
    }

    //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void Line::init() {
        // 设置类型
        setType(straightLine);
        // 父类初始化
        ComponentRotatable::init();
        ComponentStylized::init();
        // 添加图形SVG
        SVGILine = std::make_shared<Lewzen::SVGIPath>();
        SVGICurve = std::make_shared<Lewzen::SVGIPath>();
        SVGIVerticalLine = std::make_shared<Lewzen::SVGIPath>();
        SVGIHorizontalLine = std::make_shared<Lewzen::SVGIPath>();

        SVGIG->add(SVGILine);
        // 初始化关键点表
        startPoint = createCorePoint("start", 200, 200);
        endPoint = createCorePoint("end", 100, 100);
        startPoint->setVirtual(0);
        endPoint->setVirtual(0);
        std::string id = "mid";
        ndSize++;
        midPoint = createCorePoint(id,
                                   (startPoint->getX() + endPoint->getX()) / 2,
                                   (startPoint->getY() + endPoint->getY()) / 2);
        midPoint->setVirtual(1);
        pointList.push_back(startPoint);
        pointList.push_back(midPoint);
        pointList.push_back(endPoint);
        //std::cout<<"s v "<<startPoint->getVirtual()<<std::endl;
        //std::cout<<"m v "<<midPoint->getVirtual()<<std::endl;
        //std::cout<<"e v "<<endPoint->getVirtual()<<std::endl;
        // 注册关键点
        setCorePoints(pointList);

        // 绑定属性
        std::function<std::string()> _getD = std::bind(&Line::getD, this);
        SVGILine->D.bind(_getD);

        // 默认样式
        setStyle("stroke: black; fill: none; stroke-width: 1px;");
//
        SVGILine->MarkerEnd = "url(#end_arrow)";

        std::function<std::string()> _getCurveD = std::bind(&Line::getCurveD,this);
        SVGICurve->D.bind(_getCurveD);

        std::function<std::string()> _getVD = std::bind(&Line::getVerticalLineD,this);
        SVGIVerticalLine->D.bind(_getVD);

        std::function<std::string()> _getHD = std::bind(&Line::getHorizontalLineD,this);
        SVGIHorizontalLine->D.bind(_getHD);

//        scale(2.0,2.0);
//        flip(0,1,-200);
    }

    // 拷贝
    ComponentAbstract &Line::operator=(const ComponentAbstract &comp) {
        std::string type = getType();
        if(type == straightLine){
            // 拷贝父类
            ComponentRotatable::operator=(comp);
            auto &p = dynamic_cast<const Line &>(comp);
            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);

            for (int i = 0; i < (int) p.pointList.size(); i++) {
                if(pointList.size() <= i){
                    pointList.push_back(createCorePoint("tmp",0,0));
                }
                *pointList[i] = *(p.pointList[i]);
            }
        }
        else if(type == curve){
            ComponentRotatable::operator=(comp);

            auto &p = dynamic_cast<const Line &>(comp);

            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);
            *midPoint = *(p.midPoint);
        }
        else if(type == horizontalLine){
            // 拷贝父类
            ComponentRotatable::operator=(comp);

            auto &p = dynamic_cast<const Line &>(comp);

            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);
            *midPoint = *(p.midPoint);
        }
        else if(type == verticalLine){
            // 拷贝父类
            ComponentRotatable::operator=(comp);

            auto &p = dynamic_cast<const Line &>(comp);

            // 拷贝关键点位置
            *startPoint = *(p.startPoint);
            *endPoint = *(p.endPoint);
            *midPoint = *(p.midPoint);
        }

    }

    // 序列化，并记录已操作的
    void Line::serialize(json &j, std::vector<std::string> &processed) {
        // 父类序列化
        ComponentRotatable::serialize(j, processed);

        // (无额外私有内容)
    }

    // 反序列化
    ComponentAbstract &Line::operator=(const json &j) {
        // 父类反序列化
        ComponentRotatable::operator=(j);

        std::string type = getType();
        if(type == straightLine){
            // 注册关键点
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            for(auto &t:pointList){
                *t = *corePoints[t->getId()];
            }
        }
        else if(type == curve){
            // 注册关键点
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
        }
        else if(type == verticalLine){
            // 注册关键点
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
        }
        else if(type == horizontalLine){
            // 注册关键点
            startPoint = corePoints["start"];
            endPoint = corePoints["end"];
            midPoint = corePoints["mid"];
        }
    }


    //// Basics虚接口
    // 移动关键点
    void Line::moveCorePoint(const std::string &id, const double &_dx, const double &_dy) {
        auto delta = vectorFromCanvas(Lewzen::canvas_point(_dx, _dy)); // 计算组件坐标系的Δ
        double dx = delta.get_x(), dy = delta.get_y();
        std::string type = getType();
        if(type == straightLine){
            int realId = -1;
            for (int i = 0; i < (int) pointList.size(); i++) {
                if (pointList[i]->getId() == id) {
                    realId = i;
                    break;
                }
            }
            if (realId == -1) {
                //std::cout << "id wrong" << std::endl;
                return;
            }
            auto now = pointList[realId];

            if (now->getVirtual() == 0) {
                //不透明关键点

                *now += createPoint(dx, dy);
                if (now->getId() != "start" && now->getId() != "end") {
                    auto nextP = pointList[realId + 2];
                    auto preP = pointList[realId - 2];
                    Lewzen::Point2D a = *preP, b = *now, c = *nextP;
                    if ((b.get_x() - a.get_x()) * (c.get_y() - a.get_y()) -
                        (c.get_x() - a.get_x()) * (b.get_y() - a.get_y()) == 0) {
                        //共线，删除
                        ComponentRotatable::removeCorePoint(pointList[realId+1]->getId());
                        ComponentRotatable::removeCorePoint(pointList[realId-1]->getId());

                        pointList.erase(pointList.begin() + realId + 1);
                        pointList.erase(pointList.begin() + realId - 1);
                        now->setVirtual(1);
                    } else {
                        //不共线，修改,透明关键点
                        pointList[realId + 1]->setX((now->getX() + nextP->getX()) / 2);
                        pointList[realId + 1]->setY((now->getY() + nextP->getY()) / 2);

                        pointList[realId - 1]->setX((now->getX() + preP->getX()) / 2);
                        pointList[realId - 1]->setY((now->getY() + preP->getY()) / 2);
                    }
                } else if (now->getId() == "start") {
                    auto nextP = pointList[realId + 2];
                    pointList[realId + 1]->setX((now->getX() + nextP->getX()) / 2);
                    pointList[realId + 1]->setY((now->getY() + nextP->getY()) / 2);
                } else if (now->getId() == "end") {
                    auto preP = pointList[realId - 2];
                    pointList[realId - 1]->setX((now->getX() + preP->getX()) / 2);
                    pointList[realId - 1]->setY((now->getY() + preP->getY()) / 2);
                }
            } else {
                //透明关键点
                *now += createPoint(dx, dy);
                now->setVirtual(0);

                auto nextP = pointList[realId + 1];
                auto preP = pointList[realId - 1];
                std::string name1 = "mid" + std::to_string(ndSize++);
                std::string name2 = "mid" + std::to_string(ndSize++);

                auto m1 = createCorePoint(name1, (now->getX() + preP->getX()) / 2, (now->getY() + preP->getY()) / 2);
                auto m2 = createCorePoint(name2, (now->getX() + nextP->getX()) / 2, (now->getY() + nextP->getY()) / 2);
                m1->setVirtual(1);
                m2->setVirtual(1);
                setCorePoints({m1,m2});
                pointList.insert(pointList.begin() + realId + 1, m2);
                pointList.insert(pointList.begin() + realId, m1);

            }
            //        setCorePoints(pointList);
            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if(type == curve){
            if(id == "mid"){
                *midPoint += createPoint(dx,dy);
            }
            else if(id == "start"){
                *startPoint += createPoint(dx,dy);
            }
            else if(id == "end"){
                *endPoint += createPoint(dx,dy);
            }

            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if(type == verticalLine){
            if(id == "mid"){
                *midPoint += createPoint(dx,0);
            }
            else if(id == "start"){
                *startPoint += createPoint(dx,dy);
                midPoint->setY((startPoint->getY()+endPoint->getY())/2);
            }
            else if(id == "end"){
                *endPoint += createPoint(dx,dy);
                midPoint->setY((startPoint->getY()+endPoint->getY())/2);
            }


            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }
        else if(type == horizontalLine){
            if(id == "mid"){
                *midPoint += createPoint(0,dy);
            }
            else if(id == "start"){
                *startPoint += createPoint(dx,dy);
                midPoint->setX((startPoint->getX()+endPoint->getX())/2);
            }
            else if(id == "end"){
                *endPoint += createPoint(dx,dy);
                midPoint->setX((startPoint->getX()+endPoint->getX())/2);
            }


            onRotateCenterChanged(); // 旋转中心变化响应
            onChanged(); // 更新事件
        }

    }

    //// Scalable接口
    void Line::scale(const double &scaleX, const double &scaleY) {
        auto lastCenter = getRotateCenter();
        for(auto &p:pointList){
            p->setY(p->getY()*scaleY);
            p->setX(p->getX()*scaleX);
        }
        onRotateCenterChanged(); // 旋转中心变化响应
        onScaleChanged(lastCenter, scaleX,scaleY); // 大小变化响应
        onChanged(); // 更新事件
    }

    //// Flippable接口
    void Line::flip(const double &a, const double &b, const double &c) {
        auto A = Lewzen::canvas_point(0, 0), B = Lewzen::canvas_point(0, 0);
        auto C = getCenter();
        double theta = 0;
        if (a == 0) {
//            double ly = -c / b; A = Lewzen::canvas_point(0, ly), B = Lewzen::canvas_point(1, ly); theta = 0;
            double ly = -c / b;
            for(auto p:pointList){
                p->setY(2*ly-p->getY());
            }
        }
        else if (b == 0) {
            double lx = -c / a;
//            A = Lewzen::canvas_point(lx, 0), B = Lewzen::canvas_point(lx, 1); theta = ComponentRotatable::PI / 2;
            for(auto p:pointList){
                p->setX(2*lx-p->getX());
            }
        }
        else {
//            double ly = -c / b; double lx = -c / a; A = Lewzen::canvas_point(lx, 0), B = Lewzen::canvas_point(0, ly); theta = std::atan(-b / a);
            for(auto p:pointList){
                double x0 = p->getX(),y0 = p->getY();
                double ly = (a*b*x0-a*a*y0+b*c)/(a*a+b*b),lx = (-b*ly-c)/a;
                p->setX(2*lx-x0);
                p->setY(2*ly-y0);
            }
        }
//        auto FlippedC = Lewzen::line_symmetric(C, A, B);
//        // 等价于移动到对称位置然后旋转
//        moveTo(FlippedC.get_x(), FlippedC.get_y());
//        setTheta(theta * 2- getTheta());
        // 响应翻转
        onFlipped(a, b, c);
    }

    Lewzen::Point2D Line::getRotateCenter() const {
        //std::cout << "rote cent Line\n";
        if (corePoints.size() == 0) return createPoint(0, 0);
        return createPoint((startPoint->getX() + endPoint->getX()) / 2, (startPoint->getY() + endPoint->getY()) / 2);
    }

    //// 线条接口

    int Line::setLineType(std::string lineType) {
        if(getType() == straightLine){
            SVGIG->remove(SVGILine);
        }
        else if(getType() == curve){
            SVGIG->remove(SVGICurve);
        }
        else if(getType() == verticalLine){
            SVGIG->remove(SVGIVerticalLine);
        }
        else if(getType() == horizontalLine){
            SVGIG->remove(SVGIHorizontalLine);
        }
        setType(lineType);
        corePoints.clear();
        pointList.clear();

        if(lineType == straightLine){
            midPoint->setX((startPoint->getX()+endPoint->getX())/2);
            midPoint->setY((startPoint->getY()+endPoint->getY())/2);
            midPoint->setVirtual(1);
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if(endArrow!="null"){
                SVGILine->MarkerEnd = "url(#"+endArrow+")";
            }
            if(startArrow!="null"){
                SVGILine->MarkerStart = "url(#"+startArrow+")";
            }
            SVGIG->add(SVGILine);
        }
        else if(lineType == curve){
            midPoint->setX(endPoint->getX());
            midPoint->setY(startPoint->getY());
            midPoint->setVirtual(0);
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if(endArrow!="null"){
                SVGICurve->MarkerEnd = "url(#"+endArrow+")";
            }
            if(startArrow!="null"){
                SVGICurve->MarkerStart = "url(#"+startArrow+")";
            }
            SVGIG->add(SVGICurve);
        }
        else if(lineType == verticalLine){
            midPoint->setX((startPoint->getX()+endPoint->getX())/2);
            midPoint->setY((startPoint->getY()+endPoint->getY())/2);
            midPoint->setVirtual(0);
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if(endArrow!="null"){
                SVGIVerticalLine->MarkerEnd = "url(#"+endArrow+")";
            }
            if(startArrow!="null"){
                SVGIVerticalLine->MarkerStart = "url(#"+startArrow+")";
            }
            SVGIG->add(SVGIVerticalLine);
        }
        else if(lineType == horizontalLine){
            midPoint->setX((startPoint->getX()+endPoint->getX())/2);
            midPoint->setY((startPoint->getY()+endPoint->getY())/2);
            midPoint->setVirtual(0);
            pointList.push_back(startPoint);
            pointList.push_back(midPoint);
            pointList.push_back(endPoint);
            setCorePoints(pointList);
            if(endArrow!="null"){
                SVGIHorizontalLine->MarkerEnd = "url(#"+endArrow+")";
            }
            if(startArrow!="null"){
                SVGIHorizontalLine->MarkerStart = "url(#"+startArrow+")";
            }
            SVGIG->add(SVGIHorizontalLine);
        }


    }


    const CorePoint &Line::getStartPoint() const {
        return *startPoint;
    }

    void Line::setStartPoint(const CorePoint &start) {
        *startPoint = start;
    }

    const CorePoint &Line::getEndPoint() const {
        return *endPoint;
    }

    void Line::setEndPoint(const CorePoint &end) {
        *endPoint = end;
    }

    const std::string &Line::getStartArrow() const {
        return startArrow;
    }

    void Line::setStartArrow(const std::string &startArrow) {
        if(!arrows.count(startArrow))return;
        Line::startArrow = startArrow;
        std::string type = getType();
        if(type == straightLine){
            SVGILine->MarkerStart = "url(#" + startArrow+")";
        }
        else if(type == curve){
            SVGICurve->MarkerStart =  "url(#" + startArrow+")";
        }
        else if(type == verticalLine){
            SVGIVerticalLine->MarkerStart = "url(#" + startArrow+")";
        }
        else if(type == horizontalLine){
            SVGIHorizontalLine->MarkerStart = "url(#" + startArrow+")";
        }

    }

    const std::string &Line::getEndArrow() const {
        return endArrow;
    }

    void Line::setEndArrow(const std::string &endArrow) {
        if(!arrows.count(endArrow))return;
        //std::cout<<"endArrow\n";
        Line::endArrow = endArrow;

        std::string type = getType();
        if(type == straightLine){
            SVGILine->MarkerEnd = "url(#" + endArrow+")";
        }
        else if(type == curve){
            SVGICurve->MarkerEnd ="url(#" + endArrow+")";
        }
        else if(type == verticalLine){
            SVGIVerticalLine->MarkerEnd = "url(#" + endArrow+")";
        }
        else if(type == horizontalLine){
            SVGIHorizontalLine->MarkerEnd ="url(#" + endArrow+")";
        }
    }

    std::string Line::getD() {
        std::string res = "M " + std::to_string(startPoint->getX()) + " "
                          + std::to_string(startPoint->getY()) + " ";

        for (int i = 2; i < (int) pointList.size(); i += 2) {
            res += "L " + std::to_string(pointList[i]->getX()) + " " + std::to_string(pointList[i]->getY()) + " ";
        }
        return res;
    }
    std::string Line::getCurveD() {
        std::string res = "M " + std::to_string(startPoint->getX()) + " "+ std::to_string(startPoint->getY())
                          +" Q "+std::to_string(midPoint->getX())+ " " + std::to_string(midPoint->getY())+
                          " "+ std::to_string(endPoint->getX()) + " "+ std::to_string(endPoint->getY());
        return res;
    }

    std::string Line::getVerticalLineD() {
        std::string res = "M " + std::to_string(startPoint->getX()) + " "+ std::to_string(startPoint->getY())
                          +" L "+std::to_string(midPoint->getX())+ " " + std::to_string(startPoint->getY())+
                          " L " + std::to_string(midPoint->getX()) + " "+ std::to_string(endPoint->getY())
                          + " L "+ std::to_string(endPoint->getX()) + " "+ std::to_string(endPoint->getY());
        return res;
    }

    std::string Line::getHorizontalLineD() {
        std::string res = "M " + std::to_string(startPoint->getX()) + " "+ std::to_string(startPoint->getY())
                          +" L "+std::to_string(startPoint->getX())+ " " + std::to_string(midPoint->getY())+
                          " L " + std::to_string(endPoint->getX()) + " "+ std::to_string(midPoint->getY())
                          + " L "+ std::to_string(endPoint->getX()) + " "+ std::to_string(endPoint->getY());
        return res;
    }

    void Line::initArrow() {
        end_arrow = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow->Id = "end_arrow";
        end_arrow->MarkerHeight = 13;
        end_arrow->MarkerWidth = 13;
        end_arrow->RefX = 2;
        end_arrow->RefY = 3;
        end_arrow->Orient = "auto";
        arrowPath = std::make_shared<Lewzen::SVGIPath>();
        arrowPath->D = "M0,0 L6,3 L0,6 L2,3 L0,0";
        arrowPath->Fill = "black";
        end_arrow->add(arrowPath);

        start_arrow_circle = std::make_shared<Lewzen::SVGIMarker>();
        std::shared_ptr<Lewzen::SVGICircle> t = std::make_shared<Lewzen::SVGICircle>();
        start_arrow_circle->Id = "start_arrow_circle";
        start_arrow_circle->MarkerHeight = 13;
        start_arrow_circle->MarkerWidth = 13;
        start_arrow_circle->RefX = 2;
        start_arrow_circle->RefY = 3;
        start_arrow_circle->Orient = "auto";
        t->Cx = 2;
        t->Cy = 3;
        t->R = 2;
        t->Fill = "black";
        start_arrow_circle->add(t);

        end_arrow_circle = std::make_shared<Lewzen::SVGIMarker>();
        end_arrow_circle->Id = "end_arrow_circle";
        end_arrow_circle->MarkerHeight = 13;
        end_arrow_circle->MarkerWidth = 13;
        end_arrow_circle->RefX = 2;
        end_arrow_circle->RefY = 3;
        end_arrow_circle->Orient = "auto";
        std::shared_ptr<Lewzen::SVGICircle> t1 = std::make_shared<Lewzen::SVGICircle>();
        t1->Cx = 2;
        t1->Cy = 3;
        t1->R = 2;
        t1->Fill = "black";
        end_arrow_circle->add(t1);


        start_arrow = std::make_shared<Lewzen::SVGIMarker>();
        start_arrow->Id = "start_arrow";
        start_arrow->MarkerHeight = 13;
        start_arrow->MarkerWidth = 13;
        start_arrow->RefX = 2;
        start_arrow->RefY = 3;
        start_arrow->Orient = "auto";
        std::shared_ptr<Lewzen::SVGIPath>enda = std::make_shared<Lewzen::SVGIPath>();
        enda->D = "M4,3 L6,0 L0,3 L6,6 L4,3";
        enda->Fill = "black";
        start_arrow->add(enda);

        arrows["end_arrow"] = end_arrow;
        arrows["start_arrow"] = start_arrow;
        arrows["start_arrow_circle"] = start_arrow_circle;
        arrows["end_arrow_circle"] = end_arrow_circle;

        Defs.push_back(end_arrow);
        Defs.push_back(start_arrow_circle);
        Defs.push_back(end_arrow_circle);
        Defs.push_back(start_arrow);

        for(auto p:Defs){
            auto pp = p.lock();
            pp->commit();
        }
    }


}

