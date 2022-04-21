//
// Created by l'l on 2022/4/17.
//

#include "respons.h"
respons::respons() {

}


respons::~respons() {
    delete canva;
}
Json::Value respons:: createSvg(int shapeid){
    cout<<"shapeid "<<shapeid<<endl;
    string svg = canva->createElementAtPosition(shapeid,10,10);
    cout<<svg<<endl;
    Json::Value root;
    root["svg_id"] = canva->getFrontSvgId(canva->size-1);
    cout<<canva->size-1<<endl;
    root["svg"] = svg;
    root["type"]= "create";
    root["g_id"]=canva->size-1;
    return root;
}

Json::Value respons::getCore(int svgId){
    vector<point> tmp = canva->getCore(svgId);

    Json::Value X;
    Json::Value Y;
    Json::Value position;
    for(int i=0;i<(int)tmp.size();i++){
        X[i] = tmp[i].x;
        Y[i] = tmp[i].y;
    }
    Json::Value root;
    position["X"] = X;
    position["Y"] = Y;
    root["type"] = "core";
    root["position"] = position;
    root["svg_id"]=canva->getFrontSvgId(svgId);
    return root;
}


Json::Value respons::elementScale(int core_id,int svgId,double move_x,double move_y){
    string svg_id=canva->getFrontSvgId(svgId);

    map<string,Json::Value >dom_change;

    canva->degreeElement(svgId,core_id,move_x,move_y);

    vector<point> tmp = canva->getCore(svgId);

    for(int i=0;i<(int)tmp.size();i++){
        Json::Value item;
        item["cx"]=tmp[i].x;
        item["cy"]=tmp[i].y;
        string core_id=svg_id+"_"+ to_string(i);
        dom_change[core_id]=item;
    }
    Json::Value root;
    Json::Value avg;

    map<string,int> args = canva->getChangeSvg(svgId);
    Json::Value item;
    for(auto it = args.begin();it!=args.end();it++){
        item[it->first] = it->second;
    }
    dom_change[svg_id]=item;
    for(auto it = dom_change.begin();it!=dom_change.end();it++){
        avg[it->first]=it->second;
    }


    root["dom_change"]=avg;
    root["type"]="scale";
    root["svg_id"]=canva->getFrontSvgId(svgId);
    return root;
}

Json::Value respons::elementmove(int svgId,double move_x,double move_y){

    string svg_id=canva->getFrontSvgId(svgId);

    map<string,Json::Value >dom_change;

    canva->moveElement(svgId,move_x,move_y);
    vector<point> tmp = canva->getCore(svgId);

    for(int i=0;i<(int)tmp.size();i++){
        Json::Value item;
        item["cx"]=tmp[i].x;
        item["cy"]=tmp[i].y;
        string core_id=svg_id+"_"+ to_string(i);
        dom_change[core_id]=item;
    }
    Json::Value root;
    Json::Value avg;

    map<string,int> args = canva->getChangeSvg(svgId);
    Json::Value item;
    for(auto it = args.begin();it!=args.end();it++){
        item[it->first] = it->second;
    }
    dom_change[svg_id]=item;
    for(auto it = dom_change.begin();it!=dom_change.end();it++){
        avg[it->first]=it->second;
    }


    root["dom_change"]=avg;
    root["type"]="move";
    root["svg_id"]=canva->getFrontSvgId(svgId);
    cout<<svgId<<" svgId \n";
    return root;
}

Json::Value respons::getReturn(const Json::Value &args) {
    string type = args["type"].asString();
    std::cout<<type<<std::endl;
    Json::Value root;
    if(type == "create"){
        int id = args["shape_id"].asInt();
        root = createSvg(id);
    }
    else if(type == "core"){
        int id = args["g_id"].asInt();
        root = getCore(id);
    }
    else if(type == "scale"){
        int core_id = args["core_id"].asInt();
        int svgId = args["g_id"].asInt();
        double move_x = args["move_x"].asDouble();
        double move_y = args["move_y"].asDouble();
        root = elementScale(core_id,svgId,move_x,move_y);
    }
    else if(type == "move"){
        root = elementmove(args["g_id"].asInt(),args["move_x"].asDouble(),args["move_y"].asDouble());
    }
    return root;
}
//{"type":"create","shape_id":0}
//{"type":"move","g_id":0,"move_x":100,"move_y":100}
//{"type":"scale","g_id":2,"core_id":7,"move_x":200,"move_y":0}
//{"type":"create","shape_id":7}
//{"type":"move","g_id":0,"move_x":100,"move_y":100}
//{"type":"scale","g_id":0,"core_id":0,"move_x":100,"move_y":100}
//{"type":"core","g_id":0}
