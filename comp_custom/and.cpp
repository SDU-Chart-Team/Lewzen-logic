#include "and.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化，初始化组件在(x, y)
    void And::init()
    {
        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("and");

        SVGIG->children({}); // 移除旧的图形
        // 添加图形SVG
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 绑定属性
        std::function<std::string()> _getD = std::bind(&And::getD, this);
        SVGIPath->D.bind(_getD);
    }
    // 拷贝
    ComponentAbstract &And::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        Rectangle::operator=(comp);
        return *this;
    }
    // 序列化，并记录已操作的
    void And::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        Rectangle::serialize(j, processed);

        // (无额外私有内容)
    }
    // 反序列化
    ComponentAbstract &And::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);
        return *this;
    }

    //// Basics虚接口
    // 移动关键点
    void And::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {
        Rectangle::moveCorePoint(id, dx, dy);
        onChanged(); // 更新事件
    }

    //// 图形接口
    const std::string And::getD() const
    {
        std::stringstream ss;
        ss << "M " << LT->getX() << " " << LT->getY() << " ";
        ss << "Q " << RT->getX() << " " << RT->getY() << " " << R->getX() << " " << R->getY() << " ";
        ss << "Q " << RB->getX() << " " << RB->getY() << " " << LB->getX() << " " << LB->getY() << " ";
        ss << "Z";
        return ss.str();
    }
}