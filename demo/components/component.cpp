#include<bits/stdc++.h>
#include "component.h"
#include "../value.h"
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
    cout<<id<<endl;
    width = valueWidth[id];
    height = valueHeight[id];
    //璁＄畻澶栧洿鐭╅樀鐐?
    recPoint[0] = point(leftUpx,leftUpy);
    recPoint[1] = point(leftUpx+width/2.0,leftUpy);
    recPoint[2] = point(leftUpx+width,leftUpy);
    recPoint[3] = point(leftUpx+width,leftUpy+height/2.0);
    recPoint[4] = point(leftUpx+width,leftUpy+height);
    recPoint[5] = point(leftUpx+width/2.0,leftUpy+height);
    recPoint[6] = point(leftUpx,leftUpy+height);
    recPoint[7] = point(leftUpx,leftUpy+height/2.0);

    isValid = 1;
}

components::~components() {

}

const string components::getFrontSvgId() const {
    return frontSvgId;
}

void components::setFrontSvgId(const string frontSvgId) {
    components::frontSvgId = frontSvgId;
}

int components::getBackSvgId() const {
    return backSvgId;
}

void components::setBackSvgId(int backSvgId) {
    components::backSvgId = backSvgId;
}

bool components::getIsValid() const {
    return isValid;
}

void components::setIsValid(bool isValid) {
    components::isValid = isValid;
}

int components::getTime() const {
    return time;
}

void components::setTime(int time) {
    components::time = time;
}

int components::getComFloor() const {
    return comFloor;
}

void components::setComFloor(int comFloor) {
    components::comFloor = comFloor;
}

int components::getComponentId() const {
    return componentId;
}

void components::setComponentId(int componentId) {
    components::componentId = componentId;
}

int components::getMode() const {
    return mode;
}

void components::setMode(int mode) {
    components::mode = mode;
}

const string components::getColor() const {
    return color;
}

void components::setColor(const string &color) {
    components::color = color;
}

double components::getWidth() const {
    return width;
}

void components::setWidth(double width) {
    components::width = width;
}

double components::getHeight() const {
    return height;
}

void components::setHeight(double height) {
    components::height = height;
}

string components:: toValidStr(int tmp){
    return "\"" + to_string(tmp) + "\"";
}


//鍒ゆ柇鐐?x,y)澶勪簬鍝釜鐭╅樀鐐逛笂锛?1涓轰笉鍦?
int components:: isOnRecPoint(double x,double y){
    for(int i=0;i<8;i++){
        if(fabs(x-recPoint[i].x)<=eps &&
           fabs(y-recPoint[i].y)<=eps){
            return i;
        }
    }
    return -1;
}

//鍒ゆ柇褰撳墠缁勪欢鏄惁鍦?x1,y1)(x2,y2)缁勬垚鐨勭煩褰㈠唴
//鍒ゆ柇澶栧洿鐭╅樀鍗冲彲
bool components:: isInRec(double x1,double y1,double x2,double y2){
    return recPoint[0].x>=x1 && recPoint[0].y>=y1
           && recPoint[4].x<=x2 && recPoint[4].y<=y2;
}

//鍒ゆ柇鐐?x,y)鏄惁鍦ㄥ綋鍓嶇粍浠跺唴閮?
bool components:: isInside(double x,double y){
    return 1;
}

//鍒ゆ柇鐐?x,y)鏄惁鍦ㄥ綋鍓嶇粍浠惰竟鐣岀偣
bool components:: isBound(double x,double y){
    return 1;
}
string components ::getSvg() {
    return "string components ::getSvg()";
}


void components::calculateBoundPoint() {

}
void components::calculateRecPoint() {
    point leftUp(10000000,10000000);
    for(int i=0;i<8;i+=2){
       if(leftUp.x>recPoint[i].x||leftUp.y>recPoint[i].y){
           leftUp = recPoint[i];
       }
    }
    point tmp[4];
    for(int i=0;i<8;i+=2){
        if(recPoint[i].x == leftUp.x && recPoint[i].y == leftUp.y){
            tmp[0] = recPoint[i];
        }

        else if(recPoint[i].y == leftUp.y){
            tmp[1] = recPoint[i];
        }

        else if(recPoint[i].x == leftUp.x){
            tmp[3] = recPoint[i];
        }

        else{
            tmp[2] = recPoint[i];
        }

    }

    for(int i=0;i<8;i+=2){
        recPoint[i] = tmp[i/2];
    }


    width = recPoint[2].x - recPoint[0].x;
    height = recPoint[4].y - recPoint[2].y;

    recPoint[1] = point((recPoint[0].x+recPoint[2].x)/2,(recPoint[0].y+recPoint[2].y)/2);
    recPoint[3] = point((recPoint[2].x+recPoint[4].x)/2,(recPoint[2].y+recPoint[4].y)/2);
    recPoint[5] = point((recPoint[4].x+recPoint[6].x)/2,(recPoint[4].y+recPoint[6].y)/2);
    recPoint[7] = point((recPoint[6].x+recPoint[0].x)/2,(recPoint[6].y+recPoint[0].y)/2);
}

void components::changeRecPoint(int th,double x,double y) {
    switch (th){
        case 0:{
            recPoint[0].x+=x;
            recPoint[0].y+=y;

            recPoint[2].y+=y;
            recPoint[6].x+=x;
            calculateRecPoint();
            break;
        }
        case 1:{

            recPoint[0].y+=y;
            recPoint[2].y+=y;

            calculateRecPoint();
            break;
        }
        case 2:{
            recPoint[2].x+=x;
            recPoint[2].y+=y;

            recPoint[0].y+=y;
            recPoint[4].x+=x;
            calculateRecPoint();
            break;
        }
        case 3:{
            recPoint[2].x+=x;
            recPoint[4].x+=x;
            calculateRecPoint();
            break;
        }
        case 4:{

            recPoint[4].y+=y;
            recPoint[4].x+=x;

            recPoint[6].y+=y;
            recPoint[2].x+=x;
            calculateRecPoint();
            break;
        }
        case 5:{
            recPoint[4].y+=y;
            recPoint[6].y+=y;
            calculateRecPoint();
            break;
        }
        case 6:{
            recPoint[6].x+=x;
            recPoint[6].y+=y;

            recPoint[0].x+=x;
            recPoint[4].y+=y;
            calculateRecPoint();
            break;
        }
        case 7:{
            recPoint[6].x+=x;
            recPoint[0].x+=x;
            calculateRecPoint();
            break;
        }
        default:
            break;
    }
}





const point *components::getRecPoint() const {
    return recPoint;
}

const vector<point> &components::getBoundPoint() const {
    return boundPoint;
}

void components::setBoundPoint(const vector<point> &boundPoint) {
    components::boundPoint = boundPoint;
}

void components::moveRecPoint(double x, double y) {
    for(int i=0;i<8;i++){
        recPoint[i].x += x;
        recPoint[i].y += y;
    }
}

vector<point> components::getCore(){
    vector<point>tmp;
    for(int i=0;i<8;i++){
        tmp.push_back(recPoint[i]);
    }
    return tmp;
}
map<string,int>components::getChangeSvg() {
    map<string,int>ret;
    ret["x"] = recPoint[0].x;
    ret["y"] = recPoint[0].y;
    ret["width"] = width;
    ret["height"] = height;
    return ret;
}

void components::moveToGrid() {

}

/*int main(){
    components *a = new components(1,1,1,1,0.0,0.0);
    cout<<a->getComFloor()<<" "<<a->getComponentId()<<endl;
    a->printRecPoint();
    system("pause");
    return 0;
}*/