
#include "component.h"

class canvas {
public:
    //画布的高和宽
    double height, width;
    //画布当前组件数量
    int size = 0;
    point nowBound[4];
    vector<components> allComponents;

    canvas();

    canvas(double h, double w);

    void setHeight(double h);

    double getHeight();

    void setWidth(double w);

    double getWidth();

    void setNowBound(point p[]);

    point *getNowBound();

    vector<components> inNowView();

    void createElementOnWindow(int id);
    // 方法介绍：在画布中间创建指定图形，且置于顶层
    // 参数介绍：id:组件标识符

    void createElementAtPosition(int id, double x, double y);
    // 方法介绍：在画布指定位置创建指定图形，且置于顶层
    // 参数介绍：id:组件标识符
    // x,y:画布的x,y坐标

    void selectRectDraw(double x1, double y1, double x2, double y2);
    // 方法介绍：在给定参数下画选择矩形，
    // 参数介绍：x1,y1:矩形左上顶点位置
    // x2,y2:矩形右下顶点位置

    void selectAllElementinRect(double x1, double y1, double x2, double y2);
    // 方法介绍：将所有完全被矩形包含的矩阵置于核心状态。其他组件全部恢复固定状态
    // 参数介绍：x1,y1:矩形左上顶点位置
    // x2,y2:矩形右下顶点位置

    void click(double x, double y, int mode = 0);
    //    方法介绍：在画布上进行点击
    //    参数介绍：x,y:画布的x,y坐标
    //    mode:核心状态转变的方式
    //    ctrl->1:直接添加而不将当前所有处于核心状态的组件转变为固定状态

    void moveCavnas(double x, double y);
//            方法介绍：将画布进行移动
//            参数介绍：x,y：画布移动距离

};

