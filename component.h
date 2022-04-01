#ifndef MIND_COMPONENT_H
#define MIND_COMPONENT_H


#include<bits/stdc++.h>

using namespace std;
class point{
    public:
        double x,y;
        point();
        point(double x,double y);
};
class components{
    public:
        //组件创建时间
        int time = 0;
        //组件处于的层
        int comFloor;
        //组件标识符
        int componentId;
        //组件当前所处状态
        //核心态：0，固定态：1
        int mode;
        //组件颜色
        string color;
        double width,height;//组件矩形的宽和高
        //外围矩阵点，recPoint[0]为左上角，顺时针计数
        point recPoint[8];
        vector<point> boundPoint;//边界点

        components();
        //构造时并计算出矩阵点与边界点
        components(int mode,int floor,int id,double x,double y);
        //参数说明：mode:组件状态，floor:层数，id:组件标识符，(x,y)左上角坐标

        //~components();
        string getColor();
        void setColor(string col);

        int getMode();
        void setMode(int m);

        int getComFloor();
        void setComFloor(int h);

        int getComponentId();
        void setComponentId(int id);


        int getTime();
        void setTime(int t);

        double getHeight();
        void setHeight(double h);

        double getWidth();
        void setWidth(double w);

        void printRecPoint(){
            cout<<"recPoint\n";
            for(int i=0;i<8;i++)
                cout<<recPoint[i].x<<" "<<recPoint[i].y<<endl;
        }
        //判断点(x,y)处于哪个矩阵点上，-1为不在
        int isOnRecPoint(double x,double y);

        //判断当前组件是否在(x1,y1)(x2,y2)组成的矩形内
        bool isInRec(double x1,double y1,double x2,double y2);

        //判断点(x,y)是否在当前组件内部
        bool isInside(double x,double y);

        //判断点(x,y)是否在当前组件边界点
        bool isBound(double x,double y);


};
#endif //MIND_COMPONENT_H