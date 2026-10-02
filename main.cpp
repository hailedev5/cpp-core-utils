#include "Logger.hpp"
#include "ScopedTimer.hpp"
#include "ThreadSafeQueue.hpp"
#include "ConfigLoader.hpp"

#include <thread>
#include <vector>
#include <string>

int main() {
    // 1. Demonstrate ConfigLoader
    // Assuming a file named "config.txt" exists with content like: port=8080
    Logger::log(Logger::Level::INFO, "Initializing application...");
    ConfigLoader config;
    if (config.load("config.txt")) {
        Logger::log(Logger::Level::INFO, "Config loaded. Port: " + config.get("port", "8080"));
    } else {
        Logger::log(Logger::Level::WARNING, "Config file not found, using defaults.");
    }

    // 2. Demonstrate ScopedTimer
    {
        ScopedTimer timer("HeavyComputationSimulation");
        
        // 3. Demonstrate ThreadSafeQueue
        ThreadSafeQueue<int> taskQueue;

        // Producer thread
        std::thread producer([&taskQueue]() {
            for (int i = 0; i < 5; ++i) {
                taskQueue.push(i);
            }
        });

        // Consumer thread
        std::thread consumer([&taskQueue]() {
            for (int i = 0; i < 5; ++i) {
                int val = taskQueue.pop();
                Logger::log(Logger::Level::INFO, "Processed item: " + std::to_string(val));
            }
        });

        producer.join();
        consumer.join();
    } // Timer prints elapsed time here

    Logger::log(Logger::Level::INFO, "Application finished successfully.");

    return 0;
}