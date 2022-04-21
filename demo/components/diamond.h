//
// Created by l'l on 2022/3/27.
//

#ifndef MIND_DIAMOND_H
#define MIND_DIAMOND_H
#include "component.h"

class diamond: public components{
public:
    point ePoint[4];
    diamond();
    diamond(int mode,int floor,int id,double x,double y);

    //向量叉乘
    double corssVector(double x1,double y1,double x2,double y2);

    //判断点(x,y)是否在当前组件内部
    bool isInside(double x,double y);

    //判断点(x,y)是否在当前组件边界点
    bool isBound(double x,double y);
};


#endif //MIND_DIAMOND_H
