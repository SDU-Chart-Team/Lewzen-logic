
#ifndef __LEWZENSERVER_INTERNALSTORAGE__
#define __LEWZENSERVER_INTERNALSTORAGE__

#include "../comp_module/comp_rotatable.h"

namespace LewzenServer
{
    class InternalStorage : virtual public ComponentRotatable
    {
    protected:
        // SVGI
        std::shared_ptr<Lewzen::SVGIPath> SVGIPath;
        std::shared_ptr<Lewzen::SVGIRect> SVGIRect;
        //
        std::shared_ptr<CorePoint> LT, L, LB, B, RB, R, RT, T, I;
        //
        bool corePointMoving = false;

    public:
        ////
        //
        virtual void init() override;
        //
        virtual ComponentAbstract &operator=(const ComponentAbstract &comp) override;
        //
        virtual void serialize(json &j, std::vector<std::string> &processed) override;
        //
        virtual ComponentAbstract &operator=(const json &j) override;

        //// Basics
        virtual void moveCorePoint(const std::string &id, const double &dx, const double &dy) override;

        ////
        //// 矩形接口
        virtual double getX() const;
        virtual double getY() const;
        virtual double getWidth() const;
        virtual double getHeight() const;
        virtual std::string getD() const;
    };
}

#endif
