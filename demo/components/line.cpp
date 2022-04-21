//
// Created by l'l on 2022/4/2.
//

#include "line.h"
#include<bits/stdc++.h>
static int counter = 0;
line::line(){

}

line::line(int mode,int floor,int id,double x,double y): components(mode,floor,id,x,y){
    ePoint.push_back(recPoint[2]);
    //ePoint.push_back(point{x+valueWidth[id]/2,y+valueHeight[id]/2});
    ePoint.push_back(recPoint[6]);
    frontSvgId = name + to_string(counter);
    counter++;
}


string line::getSvg() {
    cout<<"lineSVG\n";
    auto first = ePoint.begin();
    string x1 = toValidStr((int)(first->x)),y1 = toValidStr(first->y);
    string x2 = toValidStr((++first)->x),y2 = toValidStr(first->y);
    string res = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
                 "  <line id=\""+ frontSvgId+"\"x1=" + x1+
                 " y1="+ y1+
                 " x2="+ x2+
                 " y2="+y2+" style=\"stroke:black;stroke-width:3\" />\n"
                           "</svg>";
    return res;
}

map<string,int>line::getChangeSvg(){
    map<string,int> ret;
    auto first = ePoint.begin();
    ret["x1"] =  first->x;
    ret["y1"] = first->y;
    first++;
    ret["x2"] = first->x;
    ret["y2"] = first->y;
    return ret;
}
//婊¤冻浠ヤ笅涓や釜鏉′欢锛?
//
//锛?锛夛紙Q - P1锛?* 锛圥2 - P1锛? 0锛?
//
//锛?锛塓鍦ㄤ互P1锛孭2涓哄瑙掗《鐐圭殑鐭╁舰鍐咃紱
bool line:: onSegment(point Pi , point Pj , point Q)
{
    if((Q.x - Pi.x) * (Pj.y - Pi.y) == (Pj.x - Pi.x) * (Q.y - Pi.y)  //鍙変箻
       //淇濊瘉Q鐐瑰潗鏍囧湪pi,pj涔嬮棿
       && min(Pi.x , Pj.x) <= Q.x && Q.x <= max(Pi.x , Pj.x)
       && min(Pi.y , Pj.y) <= Q.y && Q.y <= max(Pi.y , Pj.y))
        return true;
    else
        return false;
}

//鍒ゆ柇褰撳墠缁勪欢鏄惁鍦?x1,y1)(x2,y2)缁勬垚鐨勭煩褰㈠唴
//鍒ゆ柇鎵€鏈夌偣鏄惁鍦ㄧ煩褰㈠唴
bool line:: isInRec(double x1,double y1,double x2,double y2){
    for(point tmp:ePoint){
        if(!(tmp.x >=x1 && tmp.y>=y1 && tmp.x<=x2&&tmp.y<=y2))
            return 0;
    }
    return 1;
}



//鍒ゆ柇鐐?x,y)鏄惁鍦ㄥ綋鍓嶇粍浠跺唴閮?
bool line:: isInside(double x,double y){
    auto last = ePoint.begin();
    auto it = last;
    it++;
    point Q = point(x,y);
    while(it!=ePoint.end()){
        if(onSegment(*last,*it,Q))
            return 1;
        last = it;
        it++;
    }
    return 0;
}

//鍒ゆ柇鐐?x,y)鏄惁鍦ㄥ綋鍓嶇粍浠惰竟鐣岀偣
bool line ::isBound(double x,double y){
    return 1;
}

void line::moveRecPoint(double x, double y) {
    auto it = ePoint.begin();
    while(it!=ePoint.end()){
        it->x += x;
        it->y += y;
        it++;
    }
}

void line::changeRecPoint(int th, double x, double y) {
    auto now = ePoint.begin();
    int i=0;
    while(i<th){
        i++;
        now++;
    }
    now->x += x;
    now->y += y;
}

vector<point> line::getCore() {
    vector<point>tmp;
    auto now = ePoint.begin();
    while(now!=ePoint.end()){
        tmp.push_back(*now);
        now++;
    }
    return tmp;
}

void line::moveToGrid() {
    auto first = ePoint.begin();
    int mx = (int)(first->x) % valueGrid;
    int my = (int)(first->y) % valueGrid;
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