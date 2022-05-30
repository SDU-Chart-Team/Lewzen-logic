#include "comp_factory.h"

namespace LewzenServer
{
    std::function<std::shared_ptr<ComponentAbstract>()> newRectangle = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Rectangle>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newIsometricCube = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<IsometricCube>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newLine = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Line>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newTrapezoid = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Trapezoid>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newParallelogram = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Parallelogram>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newHexagon = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Hexagon>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newArrowRight = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ArrowRight>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newArrowLeft = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ArrowLeft>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newArrowUp = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ArrowUp>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newArrowDown = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ArrowDown>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newChevron = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Chevron>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newNotched = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Notched>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newAnd = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<And>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newCircle = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Circle>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newDiamond = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Diamond>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newEllipse = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Ellipse>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newEnvelope = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Envelope>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newInternalStorage = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<InternalStorage>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newOr = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Or>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newProcess = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Process>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newRoundedRectangle = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<RoundedRectangle>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newStar = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Star>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newTriangle = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Triangle>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newCollate = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Collate>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newCard = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Card>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newCylinder = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Cylinder>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newDocument = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Document>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newStep = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Step>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newAnnotation = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Annotation>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newData = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Data>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newDatabase = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Database>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newTape = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Tape>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newDataStorage = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<DataStorage>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newActor = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Actor>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newCallout = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Callout>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newManualInput = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ManualInput>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newTapeData = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<TapeData>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newLoopLimit = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<LoopLimit>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newOffPageConnector = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<OffPageConnector>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newDelay = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Delay>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newDisplay = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Display>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newDoubleArrow = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<DoubleArrow>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newUser = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<User>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newCross = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Cross>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newCorner = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Corner>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newTee = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Tee>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newBigArrowLeft = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<BigArrowLeft>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newPlus = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Plus>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newPreparation = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Preparation>());
    };

    std::unordered_map<std::string, std::function<std::shared_ptr<ComponentAbstract>()>> ComponentFactory::newComponent = {
        {"rectangle", newRectangle},
        {"line", newLine},
        {"isometric_cube", newIsometricCube},
        {"trapezoid", newTrapezoid},
        {"parallelogram", newParallelogram},
        {"hexagon", newHexagon},
        {"arrow_right", newArrowRight},
        {"arrow_left", newArrowLeft},
        {"arrow_up", newArrowUp},
        {"arrow_down", newArrowDown},
        {"chevron", newChevron},
        {"notched", newNotched},
        {"and", newAnd},
        {"circle", newCircle},
        {"diamond", newDiamond},
        {"ellipse", newEllipse},
        {"envelope", newEnvelope},
        {"internal_storage", newInternalStorage},
        {"or", newOr},
        {"process", newProcess},
        {"rounded_rectangle", newRoundedRectangle},
        {"star", newStar},
        {"triangle", newTriangle},
        {"collate", newCollate},
        {"card", newCard},
        {"cylinder", newCylinder},
        {"document", newDocument},
        {"step", newStep},
        {"annotation", newAnnotation},
        {"data", newData},
        {"database", newDatabase},
        {"tape", newTape},
        {"data_storage", newDataStorage},
        {"actor", newActor},
        {"callout", newCallout},
        {"manual_input", newManualInput},
        {"tape_data", newTapeData},
        {"loop_limit", newLoopLimit},
        {"off_page_connector", newOffPageConnector},
        {"delay", newDelay},
        {"display", newDisplay},
        {"double_arrow", newDoubleArrow},
        {"user", newUser},
        {"cross", newCross},
        {"corner", newCorner},
        {"tee", newTee},
        {"big_arrow_left", newBigArrowLeft},
        {"plus", newPlus},
        {"preparation",newPreparation},
    };

    std::shared_ptr<ComponentAbstract> ComponentFactory::createComponent(const std::string &type)
    {
        return newComponent[type]();
    }
}