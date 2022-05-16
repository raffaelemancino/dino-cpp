/*
Copyright (C) 2022 Raffaele Francesco Mancino <raffaelefrancesco.mancino@gmail.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
Boston, MA  02110-1301, USA.
*/

#include "utils.hpp"

Logger *Logger::logger = nullptr;

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YLW "\e[0;33m"
#define MAG "\e[0;35m"

Logger *Logger::getInstance()
{
    if (!logger)
    {
        logger = new Logger();
    }

    return logger;
}

void Logger::log(std::string text)
{
    std::cout << GRN << this->prefix << text << NC << std::endl;
}

void Logger::err(std::string text)
{
    std::cout << RED << this->prefix << text << NC << std::endl;
}

void Logger::warn(std::string text)
{
    std::cout << YLW << this->prefix << text << NC << std::endl;
}

void Logger::debug(std::string text)
{
    std::cout << MAG << this->prefix << text << NC << std::endl;
}

// Name            FG  BG
// Black           30  40
// Red             31  41
// Green           32  42
// Yellow          33  43
// Blue            34  44
// Magenta         35  45
// Cyan            36  46
// White           37  47
// Bright Black    90  100
// Bright Red      91  101
// Bright Green    92  102
// Bright Yellow   93  103
// Bright Blue     94  104
// Bright Magenta  95  105
// Bright Cyan     96  106
// Bright White    97  107