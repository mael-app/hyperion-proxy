#include "utils/Logger.h"

using namespace hyperion_proxy::common::utils;

int main() {
    Logger::log("Hello and welcome to C++ in client!", Logger::LogLevel::INFO);
    return 0;
}
