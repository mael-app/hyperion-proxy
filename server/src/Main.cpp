#include <iostream>
#include "utils/ConfigLoader.h"

int main() {
    ConfigLoader loader;
    if (!loader.load("config.yaml")) {
        std::cerr << "Failed to load configuration.\n";
        return 1;
    }

    for (const auto &mapping : loader.getPortMappings()) {
        std::cout << "Public Port: " << mapping.public_port << ", Destination: " << mapping.destination_host << ":" << mapping.destination_port << '\n';
    }

    return 0;
}