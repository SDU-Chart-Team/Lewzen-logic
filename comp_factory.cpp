#include "comp_factory.h"

namespace LewzenServer
{
    std::function<std::shared_ptr<ComponentAbstract>()> newRectangle = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Rectangle>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newRectangleScriptable = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<RectangleScriptable>());
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
    // std::function<std::shared_ptr<ComponentAbstract>()> newLoopLimit = []()
    // {
    //     return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<LoopLimit>());
    // };
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
    std::function<std::shared_ptr<ComponentAbstract>()> newStart = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Start>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newTerminator = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Terminator>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newStoredData = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<StoredData>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newSort = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Sort>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newDecision = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Decision>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newManualOperation = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ManualOperation>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newNormalProcess = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<NormalProcess>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newUseCase = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<UseCase>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newEntity = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Entity>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newRelation = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Relation>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newWeakRelation = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<WeakRelation>());
    };




    std::function<std::shared_ptr<ComponentAbstract>()> newSubTopic = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<SubTopic>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newPackage = [](){
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Package>());
    };


    std::function<std::shared_ptr<ComponentAbstract>()> newSwimmingLane = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<SwimmingLane>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newFrame = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Frame>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newNotes = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Notes>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newInterfacesClasses = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Interfacesclasses>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newClasses = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Classes>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newActivities = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Activities>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newMultiInstanceClass = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<MultiInstanceClass>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newSendSignal = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<SendSignal>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newReceiveSignal = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<ReceiveSignal>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newTimeSignal = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<TimeSignal>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newDelete = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Delete>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newElement = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Element>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newLifeline = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Lifeline>());
    };
    std::function<std::shared_ptr<ComponentAbstract>()> newGeneralize = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Generalize>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newGeneralizeAll = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<GeneralizeAll>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newBind = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Bind>());
    };

    std::function<std::shared_ptr<ComponentAbstract>()> newEntityCircle = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<EntityCircle>());
    };


    std::function<std::shared_ptr<ComponentAbstract>()> newNode = []()
    {
        return std::dynamic_pointer_cast<ComponentAbstract>(std::make_shared<Node>());
    };

    std::unordered_map<std::string, std::function<std::shared_ptr<ComponentAbstract>()>> ComponentFactory::newComponent = {
        {"rectangle", newRectangle},
        {"rectangle_scriptable", newRectangleScriptable},
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
        // {"loop_limit", newLoopLimit},
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
        {"preparation", newPreparation},
        {"start", newStart},
        {"terminator", newTerminator},
        {"stored_data", newStoredData},
        {"sort", newSort},
        {"decision", newDecision},
        {"manual_operation", newManualOperation},
        {"normal_process", newNormalProcess},
        {"use_case", newUseCase},
        {"entity", newEntity},
        {"relation",newRelation},
        {"weak_relation",newWeakRelation},

        {"sub_topic",newSubTopic},
        {"package",newPackage},
        {"swimming_lane",newSwimmingLane},
        {"frame",newFrame},
        {"notes",newNotes},
        {"interfaces_classes",newInterfacesClasses},
        {"classes",newClasses},
        {"activities",newActivities},
        {"multi_instance_class",newMultiInstanceClass},
        {"send_signal",newSendSignal},
        {"receive_signal",newReceiveSignal},
        {"time_signal",newTimeSignal},
        {"delete",newDelete},
        {"element",newElement},
        {"lifeline",newLifeline},
        {"generalize",newGeneralize},
        {"generalize_all",newGeneralizeAll},
        {"bind",newBind},
        {"entity_circle",newEntityCircle},
        {"node",newNode},

    };

    std::shared_ptr<ComponentAbstract> ComponentFactory::createComponent(const std::string &type)
    {
        return newComponent[type]();
    }
}