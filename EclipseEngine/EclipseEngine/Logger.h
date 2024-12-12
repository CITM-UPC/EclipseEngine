#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <functional>

class Logger 
{
public:
    using LogCallback = std::function<void(const std::string&)>;

    static void Init(const std::string& filename = "log.txt");
    static void Log(const std::string& message);
    static void Log(const std::string& message, const std::string& item);
    static void SetCallback(LogCallback callback); // callback
    static void Close();

private:
    static std::ofstream m_LogStream;
    static LogCallback m_Callback; // Store the callback function
};

#endif // LOGGER_H
