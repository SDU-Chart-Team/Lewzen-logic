//
// Created by l'l on 2022/3/27.
//

#include "circle.h"
#include "value.h"
circle::circle() {

}

circle::circle(int mode, int floor, int id, double x, double y): components(mode,floor,id,x,y) {
    x0 = (recPoint[0].x+recPoint[4].x)/2;
    y0 = (recPoint[0].y+recPoint[4].y)/2;
    r = 50;
}
////判断点(x,y)处于哪个矩阵点上，-1为不在
//int circle:: isOnRecPoint(double x,double y){
//    for(int i=0;i<8;i++){
//        if(fabs(x-recPoint[i].x)<=eps &&
//           fabs(y-recPoint[i].y)<=eps)
//            return i;
//
//    }
//    return -1;
//}

////判断当前组件是否在(x1,y1)(x2,y2)组成的矩形内
////圆形判断外界矩阵即可
//bool circle:: isInRec(double x1,double y1,double x2,double y2){
//    return recPoint[0].x >= x1 && recPoint[0].y>=y1
//    && recPoint[4].x<=x2 && recPoint[4].y<=y2;
//}

//判断点(x,y)是否在当前组件内部

bool circle :: isInside(double x,double y){
    return (x-x0)*(x-x0)+(y-y0)*(y-y0)<=r*r;
}

//判断点(x,y)是否在当前组件边界点
bool circle:: isBound(double x,double y){
    return 1;
}
