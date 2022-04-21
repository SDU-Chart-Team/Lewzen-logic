
#include "components/component.h"
#include "components/rectangle.h"
#include "components/parashape.h"
#include "components/circle.h"
#include "components/oval.h"
#include "components/hexagon.h"
#include "components/diamond.h"
#include "components/triangle.h"
#include "components/line.h"

class canvas {
public:
    int grid=0;
    //画布的高和宽
    double height, width;
    //画布当前组件数量
    int size = 0;
    point nowBound[4];
    vector<components*> allComponents;

    canvas();

    canvas(double h, double w);

    ~canvas();
    void setHeight(double h);

    double getHeight();

    void setWidth(double w);

    double getWidth();

    void setNowBound(point p[]);

    point *getNowBound();

    vector<components> inNowView();

    string createElementOnWindow(int typeId);
    // 方法介绍：在画布中间创建指定图形，且置于顶层
    // 参数介绍：typeId:组件标识符

    string createElementAtPosition(int typeId, double x, double y);
    // 方法介绍：在画布指定位置创建指定图形，且置于顶层
    // 参数介绍：typeId:组件标识符
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
    point* keyPoint(int id);
//    方法介绍：当鼠标位于组件上时，调用该方法，会返回组件的关键点所有位置
//            id ：组件标号
    point* mouseClickElement(int id);
//    方法介绍：当鼠标位于组件上，点击以后会返回外围矩阵的所有关键点位置，同时会把该组件置为核心状态，
//    其余组件变为固定状态，选中该组件，若有重叠则处理最上层组件
//            id ：组件标号
    void  mouseClickSpace(double x,double y);
//    方法介绍：当鼠标在空白处点击以后，会把所有组件置为固定态。
//    (x,y)为鼠标位置

    string moveElement(int id,double x,double y);
//    方法介绍：在选中组件id以后，组件坐标增量(x,y)，（与鼠标坐标增量一样）
//    参数：id每个组件唯一的标号

    void degreeElement(int id,int th,double x,double y);

    void deleteElement();

    vector<point> getCore(int svgId);

    map<string,int> getChangeSvg(int svgId);


    string getFrontSvgId(int x);

    int getGrid() const;

    void setGrid(int grid);

    int getSize() const;

    void setSize(int size);

    const vector<components *> &getAllComponents() const;

    void setAllComponents(const vector<components *> &allComponents);
    //方法介绍：得到指定组件的id
    void moveTogrid();
};

