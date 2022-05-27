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
    std::function<std::shared_ptr<ComponentAbstract>()> newTrapezoid = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Trapezoid>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newParallelogram = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Parallelogram>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newHexagon = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Hexagon>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newArrowRight = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ArrowRight>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newArrowLeft = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ArrowLeft>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newArrowUp = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ArrowUp>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newArrowDown = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ArrowDown>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newChevron = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Chevron>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newNotched = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Notched>());
    };
    std::unordered_map<std::string, std::function<std::shared_ptr<ComponentAbstract>()>> ComponentFactory::newComponent = {
        { "rectangle", newRectangle },
        { "line", newLine },
        { "isometric_cube", newIsometricCube },
        {"trapezoid", newTrapezoid},
        {"parallelogram",newParallelogram},
        {"hexagon",newHexagon},
        {"arrow_right",newArrowRight},
        {"arrow_left",newArrowLeft},
        {"arrow_up",newArrowUp},
        {"arrow_down",newArrowDown},
        {"chevron",newChevron},
        {"notched",newNotched},
    };

    std::shared_ptr<ComponentAbstract> ComponentFactory::createComponent(const std::string &type) {
        return newComponent[type]();
    }
}