#ifndef __LEWZENSERVER_ROUNDEDRECTANGLE__
#define __LEWZENSERVER_ROUNDEDRECTANGLE__

#include "../comp/rectangle.h"

namespace LewzenServer
{
    class RoundedRectangle : virtual public Rectangle
    {
    protected:
        // SVGI: only Rect
        //  额外的关键点
        std::shared_ptr<CorePoint> Control;

    public:
        //// 通用虚接口
        // 非构造初始化
        virtual void init() override;
        // 拷贝
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;
        // 序列化，并记录已操作的
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        // 反序列化
        virtual ComponentAbstract &operator=(const json &j) override;

        //// Basics虚接口
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        //// 矩形接口
        const double getRx() const;
        const double getRy() const;
    };
}
#endif