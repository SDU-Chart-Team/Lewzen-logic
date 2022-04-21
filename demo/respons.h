//
// Created by l'l on 2022/4/17.
//

#ifndef WEBSOCKETSERVER_RESPONSE_H
#define WEBSOCKETSERVER_RESPONSE_H
#include "canvas.h"
#include <json/json.h>
class respons {
public:
    canvas *canva = new canvas(1000,1000);
    respons();

    ~respons();

    Json::Value createSvg(int shapeid);

    Json::Value getCore(int svgId);


    Json::Value elementScale(int core_id,int svgId,double move_x,double move_y);

    Json::Value elementmove(int svgId,double move_x,double move_y);

    Json::Value getReturn(const Json::Value &value);
};


#endif //WEBSOCKETSERVER_RESPONSE_H
