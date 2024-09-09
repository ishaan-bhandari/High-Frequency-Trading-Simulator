#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    static void log(const std::string& message);

private:
    static std::ofstream logFile;
    static std::mutex logMutex;
};

std::ofstream Logger::logFile("order_matching.log");
std::mutex Logger::logMutex;

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    logFile << message << std::endl;
    std::cout << message << std::endl;
}
