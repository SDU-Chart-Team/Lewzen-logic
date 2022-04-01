//
// Created by l'l on 2022/4/1.
//

#include "triangle.h"
triangle::triangle() {

}

triangle::triangle(int mode, int floor, int id, double x, double y): components(mode,floor,id,x,y) {
    ePoint[0] = recPoint[0];
    ePoint[1] = recPoint[3];
    ePoint[2] = recPoint[6];
}

//向量叉乘
//a（x1，y1），b（x2，y2），则a×b=（x1y2-x2y1）
double triangle:: corssVector(double x1,double y1,double x2,double y2){
    return x1*y2-x2*y1;
}
//判断点(x,y)是否在当前组件内部

bool triangle::isInside(double x, double y) {
    for(int i=0;i<4;i++){
        int j=(i+1)%4;
        if(corssVector(ePoint[j].x-ePoint[i].x,ePoint[j].y-ePoint[i].y,
                       x-ePoint[i].x,y-ePoint[i].y) <0 )
            return 0;
    }
    return 1;
}