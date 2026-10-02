#pragma once
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

class ConfigLoader {
public:
    bool load(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream is_line(line);
            std::string key;
            if (std::getline(is_line, key, '=')) {
                std::string value;
                if (std::getline(is_line, value)) {
                    config_map_[key] = value;
                }
            }
        }
        return true;
    }

    std::string get(const std::string& key, const std::string& default_val = "") const {
        auto it = config_map_.find(key);
        return (it != config_map_.end()) ? it->second : default_val;
    }

private:
    std::unordered_map<std::string, std::string> config_map_;
};