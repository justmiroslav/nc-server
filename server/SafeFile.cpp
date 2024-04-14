#include "SafeFile.hpp"

SafeFile::SafeFile() : file(filename, std::ios::app) {}

void SafeFile::writeToFile(const std::string& data) {
    std::lock_guard<std::mutex> lock(mtx);
    if (file.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        file << "Message - " << data << "; time - " << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << std::endl;
    }
}