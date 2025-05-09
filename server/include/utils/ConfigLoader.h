#pragma once

#include <yaml-cpp/yaml.h>
#include "interfaces/IConfigLoader.h"

class ConfigLoader : public IConfigLoader {
    public:
        bool load(const std::string &path) override;
        const std::vector<PortMapping> &getPortMappings() const override;

    private:
        std::vector<PortMapping> port_mappings_;
};
