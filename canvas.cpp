#include "canvas.h"
#include<bits/stdc++.h>
using namespace std;
canvas::canvas() {

}

canvas::canvas(double h, double w) {
    height = h;
    width = w;
    nowBound[0] = point(0, 0);
    nowBound[1] = point(0, width);
    nowBound[2] = point(width, height);
    nowBound[3] = point(0, height);
}

void canvas::setHeight(double h) {
    height = h;
}

double canvas::getHeight() {
    return height;
}

void canvas::setWidth(double w) {
    width = w;
}

double canvas::getWidth() {
    return width;
}

void canvas::setNowBound(point p[]) {
    for (int i = 0; i < 4; i++) {
        nowBound[i] = p[i];
    }
}

point *canvas::getNowBound() {
    return nowBound;
}

void canvas::createElementOnWindow(int id) {
// 方法介绍：在画布中间创建指定图形，且置于顶层
// 参数介绍：id:组件标识符
    size++;
    double midX = (nowBound[0].x + nowBound[3].x) / 2.0;
    double midY = (nowBound[0].y + nowBound[3].y) / 2.0;

    for (components temp: allComponents) {
        temp.setMode(1);
    }
    components tempcom(0, size, id, midX, midY);
    allComponents.push_back(tempcom);
    return;
}


void canvas::createElementAtPosition(int id, double x, double y) {
    // 方法介绍：在画布指定位置创建指定图形，且置于顶层
    // 参数介绍：id:组件标识符
    // x,y:画布的x,y坐标
    size++;
    for (components temp: allComponents) {
        temp.setMode(1);
    }
    components tempcom(0, size, id, x, y);
    allComponents.push_back(tempcom);
    return;
}


void canvas::selectRectDraw(double x1, double y1, double x2, double y2) {
    // 方法介绍：在给定参数下画选择矩形，
    // 参数介绍：x1,y1:矩形左上顶点位置
    // x2,y2:矩形右下顶点位置
}

void canvas::selectAllElementinRect(double x1, double y1, double x2, double y2) {
    // 方法介绍：将所有完全被矩形包含的矩阵置于核心状态。其他组件全部恢复固定状态
    // 参数介绍：x1,y1:矩形左上顶点位置
    // x2,y2:矩形右下顶点位置
    for (components temp: allComponents) {
        if (temp.isInRec(x1, y1, x2, y2)) {
            temp.setMode(0);
        } else {
            temp.setMode(1);
        }
    }
    return;
}

void canvas::moveCavnas(double x, double y) {
    //            方法介绍：将画布进行移动
//            参数介绍：x,y：画布移动距离
    for (int i = 0; i < 4; i++) {
        nowBound[i].x += x;
        nowBound[i].y += y;
    }
    return;
}
