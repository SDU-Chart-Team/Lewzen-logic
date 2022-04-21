//
// Created by l'l on 2022/3/27.
//
#include "component.h"
#ifndef MIND_PARASHAPE_H
#define MIND_PARASHAPE_H

//a（x1，y1），b（x2，y2），则a×b=（x1y2-x2y1）
//凸四边形为ABCD，且ABCD顺时针，待判断的点为M，则需要满足：
//
//      AB × AM>0
//
//      BC × BM>0
//
//      CD × CM>0
//
//      DA × DM>0
//
//      即可证明点M在凸四边形内部。
class parashape :public components{
public:
    point ePoint[4];

    parashape();
    parashape(int mode,int floor,int id,double x,double y);
    //向量叉乘
    double corssVector(double x1,double y1,double x2,double y2);

    //判断点(x,y)是否在当前组件内部
    bool isInside(double x,double y);

    //判断点(x,y)是否在当前组件边界点
    bool isBound(double x,double y);
};


#endif //MIND_PARASHAPE_H
