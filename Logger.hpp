#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

class Logger {
public:
    enum class Level { INFO, WARNING, ERROR };

    static void log(Level level, const std::string& message) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "[" << std::put_time(std::localtime(&now), "%T") << "] ";
        
        switch (level) {
            case Level::INFO:    std::cout << "[INFO] "; break;
            case Level::WARNING: std::cout << "[WARN] "; break;
            case Level::ERROR:   std::cout << "[ERR ] "; break;
        }
        std::cout << message << std::endl;
    }
};