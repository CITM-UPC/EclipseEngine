#include "Logger.h"

std::ofstream Logger::m_LogStream;
Logger::LogCallback Logger::m_Callback = nullptr;

void Logger::Init(const std::string& filename)
{
    m_LogStream.open(filename, std::ios::out | std::ios::trunc);
}

void Logger::Log(const std::string& message)
{
    if (m_LogStream.is_open()) { m_LogStream << message << std::endl; }
    std::cout << message << std::endl; // Print to console as well

    if (m_Callback) { m_Callback(message); } // Call the callback to log to ConsolePanel
}

void Logger::Log(const std::string& message, const std::string& item)
{
    if (m_LogStream.is_open()) { m_LogStream << message << std::endl; }
    std::cout << message << item << std::endl; 

    if (m_Callback) { m_Callback(message + item); }
}

void Logger::SetCallback(LogCallback callback)
{
    m_Callback = callback; // Set callback for external logging
}

void Logger::Close()
{
    if (m_LogStream.is_open()) { m_LogStream.close(); }
}