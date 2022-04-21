//
// Created by l'l on 2022/3/27.
//

#include "oval.h"
#include "../value.h"

oval::oval() {

}

oval::oval(int mode, int floor, int id, double x, double y): components(mode,floor,id,x,y) {
    a = valueWidth[id]/2;
    b = valueHeight[id]/2;
    c = sqrt(a*a-b*b);
    double centerx = (recPoint[0].x+recPoint[4].x)/2;
    double centery = (recPoint[0].y+recPoint[4].y)/2;

    focus1 = point(centerx+c,centery);
    focus2 = point(centerx-c,centery);
}


//判断点(x,y)是否在当前组件内部
//点到椭圆两个焦点的距离之和与椭圆长轴的关系来判断.
//距离和大于长轴,则在椭圆之外；距离和等于长轴,在椭圆上；距离和小于长轴,在椭圆内
bool oval:: isInside(double x,double y){
    double dist = sqrt((x-focus1.x)*(x-focus1.x) + (y-focus1.y)*(y-focus1.y))
            + sqrt((x-focus2.x)*(x-focus2.x) + (y-focus2.y)*(y-focus2.y));
    return dist <= 2*a;
}

//判断点(x,y)是否在当前组件边界点
bool oval:: isBound(double x,double y){
    return 1;
}