#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <iomanip>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class SafeFile {
public:
    SafeFile();
    void writeToFile(const std::string& data);
private:
    std::string filename = "request.txt";
    std::mutex mtx;
    std::ofstream file;
};