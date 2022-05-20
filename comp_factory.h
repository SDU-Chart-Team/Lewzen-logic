#ifndef __LEWZENSERVER_COMP_FACT__
#define __LEWZENSERVER_COMP_FACT__
#include <unordered_map>
#include <functional>

#include "comp_module/comp_abstract.h"
#include "comp/rectangle.h"
#include "comp/line.h"
#include "comp_custom/isometric_cube.h"

namespace LewzenServer {
    class ComponentAbstract;
    class ComponentFactory {
        static std::unordered_map<std::string, std::function<std::shared_ptr<ComponentAbstract>()>> newComponent; 
    public:
        static std::shared_ptr<ComponentAbstract> createComponent(const std::string &type);
    };
}
#endif