#pragma once

#include <string>
#include <iostream>

class Logger
{
private:
    std::string prefix = "Dino-c++ Application:\t";
    static Logger* logger;
    Logger()
    {
    }

public:
    static Logger *getInstance();

    void log(std::string);
    void warn(std::string);
    void debug(std::string);
    void err(std::string);
};