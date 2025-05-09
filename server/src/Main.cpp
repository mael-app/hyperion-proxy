#include "utils/ConfigLoader.h"
#include "utils/Logger.h"

using namespace hyperion_proxy::common::utils;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        Logger::log("Usage: " + std::string(argv[0]) + " <config.yaml>", Logger::LogLevel::ERROR);
        return 1;
    }

    ConfigLoader loader;
    if (!loader.load(argv[1])) {
        return 1;
    }

    for (const auto &mapping : loader.getPortMappings()) {
        Logger::log("Public Port: " + std::to_string(mapping.public_port) + " → " + mapping.destination_host + ":" + std::to_string(mapping.destination_port),
                    Logger::LogLevel::INFO);
    }

    return 0;
}