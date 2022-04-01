//
// Created by l'l on 2022/3/27.
//

#ifndef MIND_RECTANGLE_H
#define MIND_RECTANGLE_H
#include "component.h"
//四个角
class rectangle :public components{
public:
    point edgePoint[4];

    rectangle();
    rectangle(int mode,int floor,int id,double x,double y);
   // ~rectangle();

    //参数说明：mode:组件状态，floor:层数，id:组件标识符，(x,y)左上角坐标


    //判断点(x,y)是否在当前组件内部
    bool isInside(double x,double y);

    //判断点(x,y)是否在当前组件边界点
    bool isBound(double x,double y);

};


#endif //MIND_RECTANGLE_H
