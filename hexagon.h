//
// Created by l'l on 2022/4/1.
//

#ifndef MIND_HEXAGON_H
#define MIND_HEXAGON_H
#include "component.h"

class hexagon: public components{
public:
    point ePoint[6];

    hexagon();

    hexagon(int mode,int floor,int id,double x,double y);

    //向量叉乘
    double corssVector(double x1,double y1,double x2,double y2);

    //判断点(x,y)是否在当前组件内部
    bool isInside(double x,double y);

    //判断点(x,y)是否在当前组件边界点
    bool isBound(double x,double y);

};


#endif //MIND_HEXAGON_H
