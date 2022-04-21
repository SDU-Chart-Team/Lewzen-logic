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
    grid = 0;
}

int canvas::getGrid() const {
    return grid;
}

void canvas::setGrid(int grid) {
    canvas::grid = grid;
    if(canvas::grid == 1){
        for(auto tmp: allComponents){
            tmp->moveToGrid();
        }

    }
}

int canvas::getSize() const {
    return size;
}

void canvas::setSize(int size) {
    canvas::size = size;
}

const vector<components *> &canvas::getAllComponents() const {
    return allComponents;
}

void canvas::setAllComponents(const vector<components *> &allComponents) {
    canvas::allComponents = allComponents;
}

canvas::~canvas(){
    for(components * tmp :allComponents){
        //cout<<tmp->componentId<<endl;
        delete tmp;
    }
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

string canvas::createElementOnWindow(int typeId) {
// 鏂规硶浠嬬粛锛氬湪鐢诲竷涓棿鍒涘缓鎸囧畾鍥惧舰锛屼笖缃簬椤跺眰
// 鍙傛暟浠嬬粛锛歵ypeId:缁勪欢鏍囪瘑绗?
    double midX = (nowBound[0].x + nowBound[3].x) / 2.0;
    double midY = (nowBound[0].y + nowBound[3].y) / 2.0;
    return createElementAtPosition(typeId,midX,midY);
}


string canvas::createElementAtPosition(int typeId, double x, double y) {
    // 鏂规硶浠嬬粛锛氬湪鐢诲竷鎸囧畾浣嶇疆鍒涘缓鎸囧畾鍥惧舰锛屼笖缃簬椤跺眰
    // 鍙傛暟浠嬬粛锛歵ypeId:缁勪欢鏍囪瘑绗?
    // x,y:鐢诲竷鐨剎,y鍧愭爣
    size++;
    for (components *temp: allComponents) {
        temp->setMode(1);
    }
    components *tempcom;
    switch (typeId) {
        case 0:{
            tempcom = new rectangle(0, size, typeId, x, y);

            allComponents.push_back(tempcom);
            break;
        }
        case 7:{
            tempcom = new line(0, size, typeId, x, y);
            allComponents.push_back(tempcom);
            cout<<"line"<<endl;
            break;
        }
        default:
            return "l";
    }
    tempcom->setBackSvgId(size-1);
    return tempcom->getSvg();

    // return "1";
}


void canvas::selectRectDraw(double x1, double y1, double x2, double y2) {
    // 鏂规硶浠嬬粛锛氬湪缁欏畾鍙傛暟涓嬬敾閫夋嫨鐭╁舰锛?
    // 鍙傛暟浠嬬粛锛歺1,y1:鐭╁舰宸︿笂椤剁偣浣嶇疆
    // x2,y2:鐭╁舰鍙充笅椤剁偣浣嶇疆


}

void canvas::selectAllElementinRect(double x1, double y1, double x2, double y2) {
    // 鏂规硶浠嬬粛锛氬皢鎵€鏈夊畬鍏ㄨ鐭╁舰鍖呭惈鐨勭煩闃电疆浜庢牳蹇冪姸鎬併€傚叾浠栫粍浠跺叏閮ㄦ仮澶嶅浐瀹氱姸鎬?
    // 鍙傛暟浠嬬粛锛歺1,y1:鐭╁舰宸︿笂椤剁偣浣嶇疆
    // x2,y2:鐭╁舰鍙充笅椤剁偣浣嶇疆
    for (components *temp: allComponents) {
        if (temp->isInRec(x1, y1, x2, y2)) {
            temp->setMode(0);
        } else {
            temp->setMode(1);
        }
    }
    return;
}

void canvas::moveCavnas(double x, double y) {
    //            鏂规硶浠嬬粛锛氬皢鐢诲竷杩涜绉诲姩
//            鍙傛暟浠嬬粛锛歺,y锛氱敾甯冪Щ鍔ㄨ窛绂?
    for (int i = 0; i < 4; i++) {
        nowBound[i].x += x;
        nowBound[i].y += y;
    }
    return;
}


point* canvas::keyPoint(int id){
    return allComponents[id]->recPoint;
}

void canvas::mouseClickSpace(double x, double y) {
    for(auto *val:allComponents){
        val->setMode(1);
    }
}

string canvas::moveElement(int id, double x, double y) {

    allComponents[id]->moveRecPoint(x,y);

    return allComponents[id]->getSvg();
}

void canvas::deleteElement() {

}

void canvas::degreeElement(int id, int th, double x, double y) {
    //澶栧洿鐭╅樀鍙樺寲鎯呭喌
    allComponents[id]->changeRecPoint(th,x,y);

}

vector<point> canvas::getCore(int svgId) {
    return allComponents[svgId]->getCore();
}

map<string,int> canvas::getChangeSvg(int svgId) {
    return allComponents[svgId]->getChangeSvg();
}

string canvas::getFrontSvgId(int x){
    return allComponents[x]->getFrontSvgId();
}

void canvas::moveTogrid() {
    for(auto tmp:allComponents){
        int mx = (int)(tmp->recPoint[0].x) % valueGrid;
        int my = (int)(tmp->recPoint[0].y) % valueGrid;
        if (mx <= valueGrid/2){
            tmp->moveRecPoint(-mx,0);
        }
        else {
            tmp->moveRecPoint(valueGrid-mx,0);
        }

        if(my <= valueGrid/2){
            tmp->moveRecPoint(0,-my);
        }
        else{
            tmp->moveRecPoint(0,valueGrid-my);
        }
    }
}
