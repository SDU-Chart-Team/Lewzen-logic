//
// Created by l'l on 2022/3/27.
//

#include "parashape.h"
#include "value.h"

parashape::parashape() {

}

parashape::parashape(int mode, int floor, int id, double x, double y): components(mode,floor,id,x,y) {
    ePoint[0] = point{x+20,y};
    ePoint[1] = recPoint[2];
    ePoint[2] = point{recPoint[4].x-20,recPoint[4].y};
    ePoint[3] = recPoint[6];

}
//向量叉乘
//a（x1，y1），b（x2，y2），则a×b=（x1y2-x2y1）
double parashape:: corssVector(double x1,double y1,double x2,double y2){
    return x1*y2-x2*y1;
}


//判断点(x,y)是否在当前组件内部
bool parashape:: isInside(double x,double y){
    for(int i=0;i<4;i++){
        int j=(i+1)%4;
        if(corssVector(ePoint[j].x-ePoint[i].x,ePoint[j].y-ePoint[i].y,
                       x-ePoint[i].x,y-ePoint[i].y) <0 )
            return 0;
    }
    return 1;
}

//判断点(x,y)是否在当前组件边界点
bool parashape:: isBound(double x,double y){
    return 1;
}
