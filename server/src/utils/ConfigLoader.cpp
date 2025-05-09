#include "utils/ConfigLoader.h"
#include <iostream>

bool ConfigLoader::load(const std::string &path) {
    try {
        YAML::Node config = YAML::LoadFile(path);

        if (!config["mappings"]) {
            std::cerr << "Missing 'mappings' key in config file.\n";
            return false;
        }

        port_mappings_.clear();

        for (const auto &node : config["mappings"]) {
            PortMapping mapping;
            mapping.public_port = node["public_port"].as<int>();
            mapping.destination_host = node["destination_host"].as<std::string>();
            mapping.destination_port = node["destination_port"].as<int>();
            port_mappings_.emplace_back(mapping);
        }

        return true;
    } catch (const std::exception &e) {
        std::cerr << "Failed to load YAML config: " << e.what() << '\n';
        return false;
    }
}

const std::vector<PortMapping> &ConfigLoader::getPortMappings() const {
    return port_mappings_;
}
