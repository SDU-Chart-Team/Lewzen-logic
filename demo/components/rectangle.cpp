//
// Created by l'l on 2022/3/27.
//

#include "rectangle.h"
#include "../value.h"
#include <bits/stdc++.h>
using namespace std;

static int counter=0;

//鍒ゆ柇鐐?x,y)澶勪簬鍝釜鐭╅樀鐐逛笂锛?1涓轰笉鍦?
rectangle::rectangle() {

}
rectangle::rectangle(int mode, int floor, int id, double x, double y): components(mode,floor,id,x,y) {
    edgePoint[0] = recPoint[0];
    edgePoint[1] = recPoint[2];
    edgePoint[2] = recPoint[4];
    edgePoint[3] = recPoint[6];
    frontSvgId=name+ to_string(counter);
    counter++;
    calculateBoundPoint();
//    cout<<"rectangle_edgePoint"<<endl;
//    for(int i=0;i<4;i++)cout<<edgePoint[i].x<<" "<<edgePoint[i].y<<endl;
}

string rectangle ::getSvg() {
    return "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
           "  <rect id=\""+ frontSvgId+"\" x="+  toValidStr(recPoint[0].x)+" y="+toValidStr(recPoint[0].y)+
           " width="+toValidStr(width)+" height="+toValidStr(height)+
           " style=\"\n"
           "\t\tstroke:black;stroke-width:3;fill:white;\n"
           "\tfill-opacity:0;stroke-opacity:1.0\"/>\n"
           "</svg>";
}
map<string,int> rectangle::getChangeSvg() {
    map<string,int>ret;
    ret["x"] = recPoint[0].x;
    ret["y"] = recPoint[0].y;
    ret["width"] = width;
    ret["height"] = height;
    return ret;
}

point rectangle::calcKPoint(double k, point A, point B) {
    return point(k*(B.x-A.x)+A.x,k*(B.y-A.y)+A.y);
}
void rectangle::calculateBoundPoint() {
    for(int i=0;i<=3;i++){
        boundPoint.push_back(calcKPoint((double)i/4.0,recPoint[0],recPoint[2]));
    }

    for(int i=0;i<=3;i++){
        boundPoint.push_back(calcKPoint((double)i/4.0,recPoint[2],recPoint[4]));
    }

    for(int i=0;i<=3;i++){
        boundPoint.push_back(calcKPoint((double)i/4.0,recPoint[4],recPoint[6]));
    }

    for(int i=0;i<=3;i++){
        boundPoint.push_back(calcKPoint((double)i/4.0,recPoint[6],recPoint[0]));
    }
}


void rectangle::moveRecPoint(double x, double y) {
    for(int i=0;i<8;i++){
        recPoint[i].x += x;
        recPoint[i].y += y;
    }
}

vector<point> rectangle::getCore() {
    vector<point>tmp;
    for(int i=0;i<8;i++){
        tmp.push_back(recPoint[i]);
    }
    return tmp;
}

void rectangle::moveToGrid() {
    int mx = (int)(recPoint[0].x) % valueGrid;
    int my = (int)(recPoint[0].y) % valueGrid;
    if (mx <= valueGrid/2){
        moveRecPoint(-mx,0);
    }
    else {
        moveRecPoint(valueGrid-mx,0);
    }

    if(my <= valueGrid/2){
        moveRecPoint(0,-my);
    }
    else{
        moveRecPoint(0,valueGrid-my);
    }
}
//鍒ゆ柇鐐?x,y)鏄惁鍦ㄥ綋鍓嶇粍浠跺唴閮?
bool rectangle:: isInside(double x,double y){
    return x>=edgePoint[0].x && y>=edgePoint[0].y
           && x<=edgePoint[2].x && y<= edgePoint[2].y;
}

//鍒ゆ柇鐐?x,y)鏄惁鍦ㄥ綋鍓嶇粍浠惰竟鐣岀偣
bool rectangle::isBound(double x,double y){
    return 1;
}
