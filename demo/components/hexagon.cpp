//
// Created by l'l on 2022/4/1.
//

#include "hexagon.h"
#include "../value.h"

hexagon::hexagon() {

}

hexagon::hexagon(int mode, int floor, int id, double x, double y) : components(mode,floor,id,x,y){
    ePoint[0] = point{recPoint[0].x+20,recPoint[0].y};
    ePoint[1] = point{recPoint[2].x-20,recPoint[2].y};
    ePoint[2] = recPoint[3];
    ePoint[3] = point{recPoint[4].x-20,recPoint[4].y};

    ePoint[4] = point{recPoint[6].x+20,recPoint[6].y};
    ePoint[5] = recPoint[7];
}

//向量叉乘
//a（x1，y1），b（x2，y2），则a×b=（x1y2-x2y1）
double hexagon:: corssVector(double x1,double y1,double x2,double y2){
    return x1*y2-x2*y1;
}
//判断点(x,y)处于哪个矩阵点上，-1为不在
//int hexagon:: isOnRecPoint(double x,double y){
//    for(int i=0;i<8;i++){
//        if(fabs(x-recPoint[i].x)<=eps &&
//           fabs(y-recPoint[i].y)<=eps)
//            return i;
//    }
//    return -1;
//}


//判断点(x,y)是否在当前组件内部
bool hexagon:: isInside(double x,double y){
    for(int i=0;i<6;i++){
        int j=(i+1)%6;
        if(corssVector(ePoint[j].x-ePoint[i].x,ePoint[j].y-ePoint[i].y,
                       x-ePoint[i].x,y-ePoint[i].y) <0 )
            return 0;
    }
    return 1;
}

//判断点(x,y)是否在当前组件边界点
bool hexagon:: isBound(double x,double y){
    return 1;
}