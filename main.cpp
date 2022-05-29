#include "register.h"
#include "canvas.h"

static constexpr long double PI = 3.141592653589793238462643383279502884L;
std::vector<std::string> id;

void add(const std::string &type) {
    nlohmann::json j = nlohmann::json::parse(LewzenServer::Register::run(R"({"command": "add", "type": ")" + type + R"("})"));
    std::vector<std::string> ids = j["returns"][0]["ids"];
    id.insert(id.end(), ids.begin(), ids.end());
}

void copy() {
    nlohmann::json j = nlohmann::json::parse(LewzenServer::Register::run(R"({"command": "copy"})"));
    std::vector<std::string> ids = j["returns"][0]["ids"];
    id.insert(id.end(), ids.begin(), ids.end());
}

void test_life() {
    std::cout << LewzenServer::Register::init() << std::endl;
    std::cout << "-------" << std::endl;
    add("rectangle");
    add("rectangle");
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "link", "id1": ")" + id[0] + R"(", "id2": ")" + id[1] + R"("})") << std::endl;
    std::cout << "-------" << std::endl;

    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[0] + "\", \"" + id[1] + "\"]}") << std::endl;
    copy();
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;

    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[0] + "\"]}") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "remove", "time": 1})") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;

    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[3] + "\"]}") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "get_children"})") << std::endl;

    /*std::cout << LewzenServer::Register::run(R"({"command": "readd"})") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;

    std::cout << LewzenServer::Register::run(R"({"command": "cursor", "id": ")" + id[0] + "\"}") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "remove", "time": 2})") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;*/

    std::cout << LewzenServer::Register::run(R"({"command": "discard", "time": 1})") << std::endl;
    std::cout << "-------" << std::endl;
}

void test_basics() {
    std::cout << LewzenServer::Register::init() << std::endl;
    std::cout << "-------" << std::endl;
    add("rectangle");
    add("rectangle");
    auto p = LewzenServer::Canvas::components.begin();
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "link", "id1": ")" + id[0] + R"(", "id2": ")" + id[1] + R"("})") << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[1] + R"("]})") << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "copy"})") << std::endl;

    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": ["f62672da-9562-4c17-88db-92d21cc7431e", "ba2971ac-add2-4804-9516-b8abc975cfc9"]})") << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "get_parent"})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "move", "dx": 1000, "dy": 2000})") << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
}

void test_rotate() {
    std::cout << LewzenServer::Register::init() << std::endl;
    std::cout << "-------" << std::endl;
    add("rectangle");
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[0] + R"("]})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "set_theta", "theta": )" + std::to_string(PI / 4) + "}") << std::endl; // 设置角度
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    //std::cout << LewzenServer::Register::run(R"({"command": "move", "dx": 100, "dy": 200})") << std::endl; // 移动
    //std::cout << LewzenServer::Canvas::HTML() << std::endl;
    //std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "RB", "dx": 400, "dy": 400})") << std::endl; // 移动关键点
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    
    std::cout << "-------" << std::endl;
    add("rectangle"); // 增加第二个
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "link", "id1": ")" + id[1] + R"(", "id2": ")" + id[0] + R"("})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[1] + R"("]})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "disable_rotate_bind"})") << std::endl; // 禁用旋转绑定
    //std::cout << LewzenServer::Register::run(R"({"command": "disable_move_bind"})") << std::endl; // 禁用移动绑定
    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[0] + R"("]})") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "set_theta", "theta": )" + std::to_string(PI / 3) + "}") << std::endl; // 链接后旋转
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "move", "dx": 100, "dy": 200})") << std::endl; // 旋转后移动
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    add("rectangle"); // 增加第三个并重链接
    std::cout << LewzenServer::Register::run(R"({"command": "link", "id1": ")" + id[1] + R"(", "id2": ")" + id[2] + R"("})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "get_theta"})") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "=======" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[0] + R"(", ")" + id[2] + R"("]})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "set_style", "style": "stroke: black; fill: green; stroke-width: 3px;"})") << std::endl; // 设置样式
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[0] + R"(", ")" + id[1] + R"("]})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "set_html", "html": "<em>hel11111</em><em>111</em><u><em>111</em></u><u><em>1lo</em></u>"})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "set_alignment", "alignment": {"horizental": 0, "vertical": 0}})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "set_spacing", "spacing": {"left": -10, "right": 0, "top": 0, "bottom": 0, "global": 10}})") << std::endl; // 设置内容
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    //std::cout << LewzenServer::Register::run(R"({"command": "cursor", "id": ")" + id[2] + R"("})") << std::endl;
    //std::cout << LewzenServer::Register::run(R"({"command": "flip", "a": 1, "b": 0, "c": -120})") << std::endl; // 翻转
    //std::cout << LewzenServer::Canvas::HTML() << std::endl;
    //std::cout << "-------" << std::endl;
    //std::cout << LewzenServer::Register::run(R"({"command": "cursor", "id": ")" + id[1] + R"("})") << std::endl;
    //std::cout << LewzenServer::Register::run(R"({"command": "enable_scale_bind"})") << std::endl;
    //std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[2] + R"(", "pid": "RB", "dx": 400, "dy": 400})") << std::endl; // 移动关键点，进行缩放
    //std::cout << LewzenServer::Canvas::HTML() << std::endl;
    //std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "cursor", "id": ")" + id[2] + R"("})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "set_rect", "rect":{"height":100.0,"width":60.0,"x":100.0,"y":20.0}})") << std::endl; // 设置矩形
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "link", "id1": ")" + id[0] + R"(", "id2": ")" + id[2] + R"("})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "cover_children"})") << std::endl; // 覆盖子组件
    std::cout << LewzenServer::Register::run(R"({"command": "back"})") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "save"})") << std::endl; // 保存
}

void test_sl() {
    std::cout << LewzenServer::Register::init() << std::endl;
    std::cout << "-------" << std::endl;
    add("rectangle");
    //std::cout << LewzenServer::Register::run(R"([{"command": "cursor", "id": ")" + id[0] + R"("}, {"command": "get_points"}])") << std::endl;
    //std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
    /*add("rectangle");
    std::cout << LewzenServer::Register::run(R"([{"command": "cursor", "id": ")" + id[0] + R"("}, {"command": "get_points"}])") << std::endl;
    add("rectangle");
    std::cout << LewzenServer::Register::run(R"([{"command": "cursor", "id": ")" + id[1] + R"("}, {"command": "get_points"}])") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "save"})") << std::endl;
    std::string js = R"({"comps":[{"alignment":{"horizental":1,"vertical":1},"children":[{"alignment":{"horizental":0,"vertical":0},"children":null,"core_points":{"B":{"arrow":"","can_remove":false,"color":"","id":"B","is_virtual":false,"x":400.0,"y":500.0000462157775},"L":{"arrow":"","can_remove":false,"color":"","id":"L","is_virtual":false,"x":17.15728752538473,"y":450.0},"LB":{"arrow":"","can_remove":false,"color":"","id":"LB","is_virtual":false,"x":17.15728752538473,"y":500.0000462157775},"LT":{"arrow":"","can_remove":true,"color":"","id":"LT","is_virtual":true,"x":17.15728752538473,"y":399.9999537842225},"R":{"arrow":"","can_remove":false,"color":"","id":"R","is_virtual":false,"x":782.8427124746153,"y":450.0},"RB":{"arrow":"","can_remove":false,"color":"","id":"RB","is_virtual":false,"x":782.8427124746153,"y":500.0000462157775},"RT":{"arrow":"","can_remove":false,"color":"","id":"RT","is_virtual":false,"x":782.8427124746153,"y":399.9999537842225},"T":{"arrow":"","can_remove":false,"color":"","id":"T","is_virtual":false,"x":400.0,"y":399.9999537842225}},"html":"<em>hel11111</em><em>111</em><u><em>111</em></u><u><em>1lo</em></u>","modules":["Basics","Flippable","Rectangle","Rotatable","Scalable","Stylized","Writable"],"spacing":{"bottom":0.0,"global":10.0,"left":-10.0,"right":0.0,"top":0.0},"style":"stroke: black; fill: green; stroke-width: 3px;","theta":1.047198,"type":"rectangle"},{"alignment":{"horizental":0,"vertical":0},"children":null,"core_points":{"B":{"arrow":"","can_remove":false,"color":"","id":"B","is_virtual":false,"x":200.0,"y":300.0},"L":{"arrow":"","can_remove":true,"color":"","id":"L","is_virtual":true,"x":100.0,"y":250.0},"LB":{"arrow":"","can_remove":true,"color":"","id":"LB","is_virtual":true,"x":100.0,"y":300.0},"LT":{"arrow":"","can_remove":false,"color":"","id":"LT","is_virtual":true,"x":100.0,"y":200.0},"R":{"arrow":"","can_remove":false,"color":"","id":"R","is_virtual":false,"x":300.0,"y":250.0},"RB":{"arrow":"","can_remove":false,"color":"","id":"RB","is_virtual":true,"x":300.0,"y":300.0},"RT":{"arrow":"","can_remove":false,"color":"","id":"RT","is_virtual":false,"x":300.0,"y":200.0},"T":{"arrow":"","can_remove":false,"color":"","id":"T","is_virtual":false,"x":200.0,"y":200.0}},"html":"<em>hel11111</em><em>111</em><u><em>111</em></u><u><em>1lo</em></u>","modules":["Basics","Flippable","Rectangle","Rotatable","Scalable","Stylized","Writable"],"spacing":{"bottom":0.0,"global":10.0,"left":-10.0,"right":0.0,"top":0.0},"style":"stroke: black; fill: white; stroke-width: 1px;","theta":0.0,"type":"rectangle"}],"core_points":{"B":{"arrow":"","can_remove":true,"color":"","id":"B","is_virtual":true,"x":367.36126443459545,"y":806.5516042413919},"L":{"arrow":"","can_remove":true,"color":"","id":"L","is_virtual":true,"x":100.0,"y":450.0},"LB":{"arrow":"","can_remove":true,"color":"","id":"LB","is_virtual":true,"x":100.0,"y":806.5516042413919},"LT":{"arrow":"","can_remove":true,"color":"","id":"LT","is_virtual":true,"x":100.0,"y":93.44839575860811},"R":{"arrow":"","can_remove":true,"color":"","id":"R","is_virtual":true,"x":634.7225288691909,"y":450.0},"RB":{"arrow":"","can_remove":true,"color":"","id":"RB","is_virtual":true,"x":634.7225288691909,"y":806.5516042413919},"RT":{"arrow":"","can_remove":true,"color":"","id":"RT","is_virtual":true,"x":634.7225288691909,"y":93.44839575860811},"T":{"arrow":"","can_remove":true,"color":"","id":"T","is_virtual":true,"x":367.36126443459545,"y":93.44839575860811}},"html":"","modules":["Basics","Flippable","Rectangle","Rotatable","Scalable","Stylized","Writable"],"spacing":{"bottom":0.0,"global":10.0,"left":0.0,"right":0.0,"top":0.0},"style":"stroke: black; fill: green; stroke-width: 3px;","theta":0.0,"type":"rectangle"}],"indices":[0,1,2]})";
    std::cout << LewzenServer::Register::run(R"({"command": "load", "json": )" + js + R"(})") << std::endl;*/
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
}

void test_line() {
    std::cout << LewzenServer::Register::init() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout<<"linenn\n";
    add("line");
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "cursors", "ids": [")" + id[0] + R"("]})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "set_line_type", "line_type": "vertical_line"})") << std::endl;

    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;

    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "mid", "dx": 400, "dy": -50})") << std::endl; // 移动关键点

    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//
////    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "0.750000", "dx": 400, "dy": -50})") << std::endl; // 移动关键点
//    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
//    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_start", "x":200 , "y":200 })" ) << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_end", "x":300 , "y":200 })" ) << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//        std::cout << LewzenServer::Register::run(R"({"command": "on_offset"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "close_offset"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//
//
//    std::cout << LewzenServer::Register::run(R"({"command": "set_line_type", "line_type": "flexible_line"})") << std::endl;
//    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;


//    std::cout << LewzenServer::Register::run(R"({"command": "set_line_type", "line_type": "curve"})") << std::endl;
//    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//
//    std::cout << LewzenServer::Register::run(R"({"command": "set_end", "x":300 , "y":500 })" ) << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "mid0", "dx": 400, "dy": -50})") << std::endl; // 移动关键点
//
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "mid2", "dx": 40, "dy": 10})") << std::endl; // 移动关键点
//
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "mid", "dx": 40, "dy": -10})") << std::endl; // 移动关键点
//
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "mid -------" << std::endl;
//
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "midC", "dx": 40, "dy": -10})") << std::endl; // 移动关键点
//
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "midC-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "arrow", "dx": 40, "dy": 10})") << std::endl; // 移动关键点
//
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "arrow-------" << std::endl;
//
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "arrowC", "dx": 40, "dy": 10})") << std::endl; // 移动关键点
//
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "arrowC-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_start", "x":300 , "y":400 })" ) << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "midC", "dx": -40, "dy": -10})") << std::endl; // 移动关键点
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "arrowC", "dx": -40, "dy": 10})") << std::endl; // 移动关键点
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "mid", "dx": -20, "dy": -10})") << std::endl; // 移动关键点
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "arrow", "dx": -20, "dy": 10})") << std::endl; // 移动关键点
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_dotted_line", "dot_type": "dashed"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_dotted_line", "dot_type": "solid"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_end_arrow", "end_arrow": "end_arrow_two_tri"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_start_arrow", "start_arrow": "start_arrow_two_tri"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;


//    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
//
//    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//
//    std::cout << LewzenServer::Register::run(R"({"command": "set_end_arrow", "end_arrow": "end_arrow"})") << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_start_arrow", "start_arrow": "start_arrow"})") << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "mid", "dx": 40, "dy": 100})") << std::endl; // 移动关键点
////    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "on_offset"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
////    std::cout << LewzenServer::Register::run(R"({"command": "set_line_type", "line_type": "curve"})") << std::endl;
////    std::cout << LewzenServer::Canvas::HTML() << std::endl;
////    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_line_type", "line_type": "vertical_line"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_line_type", "line_type": "horizontal_line"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;

    std::cout << "-------" << std::endl;

//    std::cout << LewzenServer::Register::run(R"({"command": "set_line_type", "line_type": "curve_two"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "start", "dx": 400, "dy": 400})") << std::endl; // 移动关键点
//    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
//    std::cout << LewzenServer::Register::run(R"({"command": "set_end_arrow", "end_arrow": "end_arrow_circle"})") << std::endl;
//    std::cout << LewzenServer::Canvas::HTML() << std::endl;
//    std::cout << "-------" << std::endl;
}

void test_tra(){
    std::cout << LewzenServer::Register::init() << std::endl;
    std::cout << "-------" << std::endl;
    add("notched");
    std::cout << LewzenServer::Register::run(R"([{"command": "cursor", "id": ")" + id[0] + R"("}, {"command": "get_points"}])") << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "get_points"})") << std::endl;
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "ControlLeft", "dx": 20, "dy": 10})") << std::endl; // 移动关键点
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;

    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "RB", "dx": 200, "dy": 200})") << std::endl; // 移动关键点
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;

    std::cout << LewzenServer::Register::run(R"({"command": "move_point", "id": ")" + id[0] + R"(", "pid": "ControlRight", "dx": 20, "dy": 100})") << std::endl; // 移动关键点
    std::cout << LewzenServer::Canvas::HTML() << std::endl;
    std::cout << "-------" << std::endl;

}

int main () {
    test_life();
    //test_basics();
    //test_rotate();
    //test_sl();
    //test_line();
    //test_tra();

    return 0;
}