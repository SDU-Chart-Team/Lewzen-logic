//
// Created by l'l on 2022/3/27.
//

#ifndef MIND_CIRCLE_H
#define MIND_CIRCLE_H
#include "component.h"
//(x-x0)^2+(y-y0)^2=r^2;
class circle : public components{
public:
    double x0,y0,r;
    circle();

    circle(int mode,int floor,int id,double x,double y);


    //判断点(x,y)是否在当前组件内部
    bool isInside(double x,double y);

    //判断点(x,y)是否在当前组件边界点
    bool isBound(double x,double y);


};


#endif //MIND_CIRCLE_H
