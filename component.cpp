#include<bits/stdc++.h>
#include "component.h"
#include "value.h"
using namespace std;
point:: point(){

}
point:: point(double x,double y){
    this->x = x;
    this->y = y;
}

components::components(){

}
components::components(int mode,int floor,int id,double leftUpx,double leftUpy){
    this->mode = mode;
    comFloor = floor;
    componentId = id;
    color = "white";
    cout<<id<<endl;
    width = valueWidth[id];
    height = valueHeight[id];
    //计算外围矩阵点
    recPoint[0] = point(leftUpx,leftUpy);
    recPoint[1] = point(leftUpx+width/2.0,leftUpy);
    recPoint[2] = point(leftUpx+width,leftUpy);
    recPoint[3] = point(leftUpx+width,leftUpy+height/2.0);
    recPoint[4] = point(leftUpx+width,leftUpy+height);
    recPoint[5] = point(leftUpx+width/2.0,leftUpy+height);
    recPoint[6] = point(leftUpx,leftUpy+height);
    recPoint[7] = point(leftUpx,leftUpy+height/2.0);

}
string components::getColor()
{
    return color;
}
void components::setColor(string col){
    color = col;
}


int components:: getMode(){
    return mode;
}
void components:: setMode(int m){
    mode = m;
}

int components:: getComFloor(){
    return comFloor;
}
void components:: setComFloor(int floor){
    comFloor = floor;
}

int components:: getComponentId(){
    return componentId;
}
void components:: setComponentId(int id){
    componentId = id;
}


int components:: getTime(){
    return time;
}
void components:: setTime(int t){
    time = t;
}

double components:: getHeight(){
    return height;
}
void components:: setHeight(double h){
    height = h;
}

double components:: getWidth(){
    return width;
}
void components:: setWidth(double w){
    width = w;
}

//判断点(x,y)处于哪个矩阵点上，-1为不在
int components:: isOnRecPoint(double x,double y){
    for(int i=0;i<8;i++){
        if(fabs(x-recPoint[i].x)<=eps &&
        fabs(y-recPoint[i].y)<=eps){
            return i;
        }
    }
    return -1;
}

//判断当前组件是否在(x1,y1)(x2,y2)组成的矩形内
//判断外围矩阵即可
bool components:: isInRec(double x1,double y1,double x2,double y2){
    return recPoint[0].x>=x1 && recPoint[0].y>=y1
    && recPoint[4].x<=x2 && recPoint[4].y<=y2;
}

//判断点(x,y)是否在当前组件内部
bool components:: isInside(double x,double y){
    return 1;
}

//判断点(x,y)是否在当前组件边界点
bool components:: isBound(double x,double y){
    return 1;
}


/*int main(){
    components *a = new components(1,1,1,1,0.0,0.0);
    cout<<a->getComFloor()<<" "<<a->getComponentId()<<endl;
    a->printRecPoint();
    system("pause");
    return 0;
}*/