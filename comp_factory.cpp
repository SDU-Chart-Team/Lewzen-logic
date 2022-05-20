#include "comp_factory.h"

namespace LewzenServer {
    std::function<std::shared_ptr<ComponentAbstract>()> newRectangle = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Rectangle>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newIsometricCube = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<IsometricCube>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newLine = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Line>());
    };

    std::unordered_map<std::string, std::function<std::shared_ptr<ComponentAbstract>()>> ComponentFactory::newComponent = {
        { "rectangle", newRectangle },
        { "line", newLine },
        { "isometric_cube", newIsometricCube },
    };

    std::shared_ptr<ComponentAbstract> ComponentFactory::createComponent(const std::string &type) {
        return newComponent[type]();
    }
}