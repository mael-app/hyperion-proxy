#include "utils/ConfigLoader.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include "utils/Logger.h"

namespace fs = std::filesystem;
using namespace hyperion_proxy::common::utils;

bool ConfigLoader::load(const std::string &path) {

    if (!fs::exists(path)) {
        Logger::log("Configuration file not found: " + path, Logger::LogLevel::ERROR);
        return false;
    }

    auto ext = fs::path(path).extension().string();
    if (ext != ".yaml" && ext != ".yml") {
        Logger::log("Invalid config file extension. Expected .yaml or .yml", Logger::LogLevel::ERROR);
        return false;
    }

    try {
        YAML::Node config = YAML::LoadFile(path);

        if (!config["mappings"]) {
            Logger::log("Missing 'mappings' key in config file.", Logger::LogLevel::ERROR);
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

        Logger::log("Successfully loaded " + std::to_string(port_mappings_.size()) + " port mapping(s).", Logger::LogLevel::INFO);
        return true;
    } catch (const std::exception &e) {
        Logger::log("Failed to parse config: " + std::string(e.what()), Logger::LogLevel::ERROR);
        return false;
    }
}

const std::vector<PortMapping> &ConfigLoader::getPortMappings() const {
    return port_mappings_;
}
