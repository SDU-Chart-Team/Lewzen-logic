#include<bits/stdc++.h>
#include "component.h"
#include "rectangle.h"
#include "parashape.h"
#include "circle.h"
#include "oval.h"
#include "hexagon.h"
#include "diamond.h"
#include "triangle.h"
using namespace std;
void testCircle(){
    circle cir(1,3,2,100,100);
    cir.isInside(150,150);
}

void testParashape(){
    parashape para(1,2,1,100,100);
    cout<<para.isInside(150,150)<<endl;
}

void testOval(){
    oval ova(1,4,3,100,100);
    ova.isInside(150,150);
}

void testHexagon(){
    hexagon han(1,5,4,100,100);
    han.isInside(150,150);
    cout<<"LL"<<han.isInRec(0,0,300,300);
    cout<<"dd"<<han.isOnRecPoint(100,100);
}

void testDiamond(){
    diamond dia(1,1,5,100,100);
    dia.isInside(130,130);
}

void testTriangle(){
    triangle tri(1,1,6,100,100);
    tri.isInside(130,130);
}
int main(){
//    components *b = new components(1,1,1,0.0,0.0);
//    //cout<<a->getComFloor()<<" "<<a->getComponentId()<<endl;
//    b->printRecPoint();
//    rectangle rec(1,1,0,0.0,0.0) ;
//      rec.~rectangle();
//    rec.printRecPoint();
//    cout<<rec.isInside(0.5,0.5)<<endl;
//
//    testParashape();
//    testCircle();
//    testOval();
//    testHexagon();
//    testDiamond();
    testTriangle();
    return 0;
}

