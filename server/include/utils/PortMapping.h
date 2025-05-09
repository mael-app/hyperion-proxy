#pragma once

#include <string>

struct PortMapping {
        int public_port;
        std::string destination_host;
        int destination_port;
};
