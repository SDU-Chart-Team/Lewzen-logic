#ifndef __LEWZENSERVER_CORE_P__
#define __LEWZENSERVER_CORE_P__
#include "../release/lewzen-core/core.h"
#include "../utils/json.hpp"

namespace LewzenServer {
    using nlohmann::json;
    class CorePoint : public Lewzen::Point2D {
    private:
        std::string _color;
        bool _is_virtual;
        bool _can_remove;
        std::string _arrow;
        std::string _id;
        std::function<void()> _on_remove;
        using Lewzen::Point2D::get_x;
        using Lewzen::Point2D::set_x;
        using Lewzen::Point2D::get_y;
        using Lewzen::Point2D::set_y;
        using Lewzen::Point2D::get_coordinate_system;
    public:
        CorePoint(const CorePoint &p); 
        CorePoint(const std::string &id, const double &x, const double &y, const std::shared_ptr<Lewzen::CoordinateSystem> &coordinate_system);
        CorePoint(const std::string &id, const std::shared_ptr<Lewzen::CoordinateSystem> &coordinate_system);
        const std::string getId() const;
        std::shared_ptr<Lewzen::CoordinateSystem> getCoordinateSystem() const;
        const std::string getColor() const;
        void setColor(const std::string &color);
        bool getVirtual() const;
        void setVirtual(const bool &isVirtual);
        bool getCanRemove() const;
        void setCanRemove(const bool &canRemove);
        const std::string getArrow() const;
        void setArrow(const std::string &arrow);
        double getX() const;
        void setX(const double &x);
        double getY() const;
        void setY(const double &y);
        const std::string toString(const std::string &componentId = "");
        void serialize(json &j);
        void deserialize(const json &j);
        std::shared_ptr<CorePoint> clone();
        bool operator<(const CorePoint &b);
        CorePoint &operator=(const Lewzen::Point2D &b);
        void on_remove(const std::function<void()> callback);
        void on_remove();
    };
}
#endif