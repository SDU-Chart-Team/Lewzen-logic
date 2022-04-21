//
// Created by l'l on 2022/4/2.
//

#ifndef MIND_LINE_H
#define MIND_LINE_H
#include "component.h"
#include "../value.h"
#include <bits/stdc++.h>

class line : public components{
public:
    const string name = "line_";
    list<point>ePoint;
    line();

    line(int mode,int floor,int id,double x,double y);

    //获取svg
    string getSvg();

    //改变recPoint
    virtual void changeRecPoint(int th,double x,double y);

    //组建移动(x,y)后计算recPoint
    void moveRecPoint(double x,double y);

    //判断点是否在线段上
    bool onSegment(point Pi , point Pj , point Q);
    //判断当前组件是否在(x1,y1)(x2,y2)组成的矩形内
    bool isInRec(double x1,double y1,double x2,double y2);

    //判断点(x,y)是否在当前组件内部
    bool isInside(double x,double y);

    //判断点(x,y)是否在当前组件边界点
    bool isBound(double x,double y);

    vector<point> getCore();

    map<string,int>getChangeSvg();

    void moveToGrid();
};


#endif //MIND_LINE_H
