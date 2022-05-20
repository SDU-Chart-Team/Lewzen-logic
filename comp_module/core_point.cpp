#include "core_point.h"

namespace LewzenServer {
    CorePoint::CorePoint(const CorePoint &p): Lewzen::Point2D(p.getX(), p.getY(), p.getCoordinateSystem()), _id(p.getId()), _color(p.getColor()), _arrow(p.getArrow()), _is_virtual(p.getVirtual()) {} 
    CorePoint::CorePoint(const std::string &id, const double &x, const double &y, const std::shared_ptr<Lewzen::CoordinateSystem> &coordinate_system): Lewzen::Point2D(x, y, coordinate_system), _id(id), _color(""), _arrow(""), _is_virtual(false) {}
    CorePoint::CorePoint(const std::string &id, const std::shared_ptr<Lewzen::CoordinateSystem> &coordinate_system): Lewzen::Point2D(0, 0, coordinate_system), _id(id), _color(""), _arrow(""), _is_virtual(false) {}
    const std::string CorePoint::getId() const {
        return _id;
    }
    std::shared_ptr<Lewzen::CoordinateSystem> CorePoint::getCoordinateSystem() const {
        return Lewzen::Point2D::get_coordinate_system();
    }
    const std::string CorePoint::getColor() const {
        return _color;
    }
    void CorePoint::setColor(const std::string &color) {
        _color = color;
    }
    bool CorePoint::getVirtual() const {
        return _is_virtual;
    }
    void CorePoint::setVirtual(const bool &isVirtual) {
        _is_virtual = isVirtual;
    }
    bool CorePoint::getCanRemove() const {
        return _can_remove;
    }
    void CorePoint::setCanRemove(const bool &canRemove) {
        _can_remove = canRemove;
    }
    const std::string CorePoint::getArrow() const {
        return _arrow;
    }
    void CorePoint::setArrow(const std::string &arrow) {
        _arrow = arrow;
    }
    double CorePoint::getX() const {
        return Lewzen::Point2D::get_x();
    }
    void CorePoint::setX(const double &x) {
        Lewzen::Point2D::set_x(x);
    }
    double CorePoint::getY() const {
        return Lewzen::Point2D::get_y();
    }
    void CorePoint::setY(const double &y) {
        Lewzen::Point2D::set_y(y);
    }
    const std::string CorePoint::toString(const std::string &componentId) {
        json j; serialize(j);
        if (componentId != "") j["comp_id"] = componentId;
        return j.dump();
    }
    void CorePoint::serialize(json &j) {
        j["id"] = _id;
        j["color"] = _color;
        j["is_virtual"] = _is_virtual;
        j["can_remove"] = _can_remove;
        j["arrow"] = _arrow;
        j["x"] = get_x();
        j["y"] = get_y();
    }
    void CorePoint::deserialize(const json &j) {
        _id = j["id"];
        _color = j["color"];
        _is_virtual = j["is_virtual"];
        _can_remove = j["can_remove"];
        _arrow = j["arrow"];
        set_x(j["x"]);
        set_y(j["y"]);
    }
    std::shared_ptr<CorePoint> CorePoint::clone() {
        return std::make_shared<CorePoint>(*this);
    }
    bool CorePoint::operator<(const CorePoint &b) {
        return _id < b._id;
    }
    CorePoint &CorePoint::operator=(const Lewzen::Point2D &b) {
        Lewzen::Point2D::operator=(b);
        return *this;
    }
    void CorePoint::on_remove(const std::function<void()> callback) {
        _on_remove = callback;
    }
    void CorePoint::on_remove() {
        _on_remove = [](){};
    }
}