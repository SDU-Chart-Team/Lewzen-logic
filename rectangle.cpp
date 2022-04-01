//
// Created by l'l on 2022/3/27.
//

#include "rectangle.h"
#include "value.h"
#include <bits/stdc++.h>
using namespace std;
//判断点(x,y)处于哪个矩阵点上，-1为不在
rectangle::rectangle() {

}
rectangle::rectangle(int mode, int floor, int id, double x, double y): components(mode,floor,id,x,y) {
    edgePoint[0] = recPoint[0];
    edgePoint[1] = recPoint[2];
    edgePoint[2] = recPoint[4];
    edgePoint[3] = recPoint[6];
//    cout<<"rectangle_edgePoint"<<endl;
//    for(int i=0;i<4;i++)cout<<edgePoint[i].x<<" "<<edgePoint[i].y<<endl;
}


//判断点(x,y)是否在当前组件内部
bool rectangle:: isInside(double x,double y){
    return x>=edgePoint[0].x && y>=edgePoint[0].y
    && x<=edgePoint[2].x && y<= edgePoint[2].y;
}

//判断点(x,y)是否在当前组件边界点
bool rectangle::isBound(double x,double y){
    return 1;
}