#include "register.h"
#include <emscripten/bind.h>

using namespace emscripten;

std::string server_init() {
    return LewzenServer::Register::init();
}

std::string server_run(std::string cmd) {
    return LewzenServer::Register::run(cmd);
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("server_init", &server_init);
    function("server_run", &server_run);
}