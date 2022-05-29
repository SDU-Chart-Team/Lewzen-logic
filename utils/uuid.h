#ifndef __LEWZENSERVER_UUID__
#define __LEWZENSERVER_UUID__
#include <random>
#include <sstream>
#include <chrono>

namespace uuid {
    std::string generate_uuid_v4();
}
#endif