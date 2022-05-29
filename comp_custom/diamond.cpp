#include "diamond.h"
#include "../canvas.h"

namespace LewzenServer
{
    //// 通用虚接口
    // 非构造初始化
    void Diamond::init()
    {

        // 父类初始化
        Rectangle::init();
        // 设置类型
        setType("diamond");

        // 维护图形SVG
        SVGIG->children({});                // 移除旧的图形
        Rectangle::moveCorePoint("RB", -100, 0); // 将区域变更为方形
        SVGIPath = std::make_shared<Lewzen::SVGIPath>();
        SVGIG->add(SVGIPath);

        // 绑定图形属性
        std::function<std::string()> _getPath = std::bind(&Diamond::getPath, this);
        SVGIPath->D.bind(_getPath);
    }
    //
    ComponentAbstract &Diamond::operator=(const ComponentAbstract &comp)
    {
        // 拷贝父类
        Rectangle::operator=(comp);

        auto &p = dynamic_cast<const Diamond &>(comp);
        return *this;
    }
    // 序列化，并记录已操作的
    void Diamond::serialize(json &j, std::vector<std::string> &processed)
    {
        // 父类序列化
        Rectangle::serialize(j, processed);
    }
    //
    ComponentAbstract &Diamond::operator=(const json &j)
    {
        // 父类反序列化
        Rectangle::operator=(j);
        return *this;
    }

    //// Basics虚接口
    void Diamond::moveCorePoint(const std::string &id, const double &dx, const double &dy)
    {

        Rectangle::moveCorePoint(id, dx, dy);

        onChanged(); // 更新事件
    }

    //// Diamond接口
    const std::string Diamond::getPath() const
    {
        std::stringstream ss;
        ss << "M " << T->getX() << " " << T->getY() << " ";
        ss << "L " << R->getX() << " " << R->getY() << " ";
        ss << "L " << B->getX() << " " << B->getY() << " ";
        ss << "L " << L->getX() << " " << L->getY() << " ";
        ss << "Z";
        return ss.str();
    }
}
