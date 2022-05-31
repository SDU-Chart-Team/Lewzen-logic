#include "entity.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void Entity::init()
    {

        //
        Rectangle::init();
        // 设置类型
        setType("entity");

    }
    //
    ComponentAbstract &Entity::operator=(const ComponentAbstract &comp)
    {
        //
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Entity &>(comp);
        return *this;
    }
    //
    void Entity::serialize(json &j, std::vector<std::string> &processed)
    {
        //
        Rectangle::serialize(j, processed);

        //
    }
    //
    ComponentAbstract &Entity::operator=(const json &j)
    {
        //
        Rectangle::operator=(j);
        return *this;

    }

    //// Basics
    //
    void Entity::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged();
    }

}
