
    #ifndef __LEWZENSERVER_TRIANGLE__
#define __LEWZENSERVER_TRIANGLE__

#include "../comp/rectangle.h"

namespace LewzenServer
{
    class Triangle : virtual public Rectangle
    {
    protected:
        // SVGI
        std::shared_ptr<Lewzen::SVGIPath> SVGIPath;


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

        const std::string getD() const;
    };
}

#endif
    