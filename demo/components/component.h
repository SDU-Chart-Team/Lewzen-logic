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
    string frontSvgId;//组件id

    int backSvgId;
    //当前组件是否有效，创建时置一，删除时置0
    bool isValid = 0;
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

    virtual ~components();

    void printRecPoint(){
        cout<<"recPoint\n";
        for(int i=0;i<8;i++)
            cout<<recPoint[i].x<<" "<<recPoint[i].y<<endl;
    }
    //计算recPoint，已知四个角坐标
    void calculateRecPoint();

    //改变recPoint
    virtual void changeRecPoint(int th,double x,double y);

    //计算boundPoint
    virtual void calculateBoundPoint();

    //将数字转换为带引号的数字
    string toValidStr(int tmp);

    //获得组件的svg
    virtual string getSvg();

    //组建移动(x,y)后计算recPoint
    virtual void moveRecPoint(double x,double y);

    virtual vector<point> getCore();

    //判断点(x,y)处于哪个矩阵点上，-1为不在
    int isOnRecPoint(double x,double y);

    //判断当前组件是否在(x1,y1)(x2,y2)组成的矩形内
    bool isInRec(double x1,double y1,double x2,double y2);

    //判断点(x,y)是否在当前组件内部
    bool isInside(double x,double y);

    //判断点(x,y)是否在当前组件边界点
    bool isBound(double x,double y);

    virtual map<string,int>getChangeSvg();


    const point *getRecPoint() const;

    const vector<point> &getBoundPoint() const;

    void setBoundPoint(const vector<point> &boundPoint);

    const string getFrontSvgId() const;

    void setFrontSvgId(const string frontSvgId);

    int getBackSvgId() const;

    void setBackSvgId(int backSvgId);

    bool getIsValid() const;

    void setIsValid(bool isValid);

    int getTime() const;

    void setTime(int time);

    int getComFloor() const;

    void setComFloor(int comFloor);

    int getComponentId() const;

    void setComponentId(int componentId);

    int getMode() const;

    void setMode(int mode);

    const string getColor() const;

    void setColor(const string &color);

    double getWidth() const;

    void setWidth(double width);

    double getHeight() const;

    void setHeight(double height);


    virtual void moveToGrid();
};
#endif //MIND_COMPONENT_H