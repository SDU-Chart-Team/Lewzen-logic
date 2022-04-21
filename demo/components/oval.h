//
// Created by l'l on 2022/3/27.
//
#include "component.h"
#ifndef MIND_OVAL_H
#define MIND_OVAL_H

//
class oval : public components{
public:
    //半长轴，半短轴，半焦距
    double a,b,c;
    point focus1,focus2;
    oval();

    oval(int mode,int floor,int id,double x,double y);


    //判断点(x,y)是否在当前组件内部
    bool isInside(double x,double y);

    //判断点(x,y)是否在当前组件边界点
    bool isBound(double x,double y);

};


#endif //MIND_OVAL_H
