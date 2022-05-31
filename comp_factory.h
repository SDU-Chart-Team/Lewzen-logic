#ifndef __LEWZENSERVER_COMP_FACT__
#define __LEWZENSERVER_COMP_FACT__
#include <unordered_map>
#include <functional>

#include "comp_module/comp_abstract.h"
#include "comp/rectangle.h"
#include "comp/line.h"
#include "comp_custom/isometric_cube.h"
#include "comp_custom/trapezoid.h"
#include "comp_custom/parallelogram.h"
#include "comp_custom/hexagon.h"
#include "comp_custom/arrowRight.h"
#include "comp_custom/arrowLeft.h"
#include "comp_custom/arrowUp.h"
#include "comp_custom/arrowDown.h"
#include "comp_custom/chevron.h"
#include "comp_custom/notched.h"
#include "comp_custom/and.h"
#include "comp_custom/or.h"
#include "comp_custom/circle.h"
#include "comp_custom/diamond.h"
#include "comp_custom/ellipse.h"
#include "comp_custom/envelope.h"
#include "comp_custom/internal_storage.h"
#include "comp_custom/process.h"
#include "comp_custom/rounded_rectangle.h"
#include "comp_custom/star.h"
#include "comp_custom/triangle.h"
#include "comp_custom/collate.h"
#include "comp_custom/cylinder.h"
#include "comp_custom/card.h"
#include "comp_custom/document.h"
#include "comp_custom/step.h"
#include "comp_custom/annotation.h"
#include "comp_custom/data.h"
#include "comp_custom/database.h"
#include "comp_custom/tape.h"
#include "comp_custom/data_storage.h"
#include "comp_custom/actor.h"
#include "comp_custom/callout.h"
#include "comp_custom/manual_input.h"
#include "comp_custom/tape_data.h"
// #include "comp_custom/loop_limit.h"
#include "comp_custom/off_page_connector.h"
#include "comp_custom/delay.h"
#include "comp_custom/display.h"
#include "comp_custom/double_arrow.h"
#include "comp_custom/user.h"
#include "comp_custom/cross.h"
#include "comp_custom/corner.h"
#include "comp_custom/tee.h"
#include "comp_custom/big_arrow_left.h"
#include "comp_custom/plus.h"
#include "comp_custom/preparation.h"
#include "comp_custom/start.h"
#include "comp_custom/terminator.h"
#include "comp_custom/stored_data.h"
#include "comp_custom/sort.h"
#include "comp_custom/decision.h"
#include "comp_custom/manual_operation.h"
#include "comp_custom/normal_process.h"
#include "comp_custom/use_case.h"
#include "comp_custom/entity.h"
#include "comp_custom/relation.h"
#include "comp_custom/weak_relation.h"




namespace LewzenServer {
    class ComponentAbstract;
    class ComponentFactory {
        static std::unordered_map<std::string, std::function<std::shared_ptr<ComponentAbstract>()>> newComponent; 
    public:
        static std::shared_ptr<ComponentAbstract> createComponent(const std::string &type);
    };
}
#endif