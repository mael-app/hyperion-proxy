#pragma once

#include <string>
#include <vector>
#include "utils/PortMapping.h"

class IConfigLoader {
    public:
        virtual ~IConfigLoader() = default;

        virtual bool load(const std::string &path) = 0;

        virtual const std::vector<PortMapping> &getPortMappings() const = 0;
};
