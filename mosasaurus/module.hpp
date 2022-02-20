#ifndef MODULE
#define MODULE

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "models.hpp"

namespace Mosasaurus
{
    class MosaModule

    {
    private:
        std::map<std::string, IoC::Injectable *> services;
        std::map<std::string, IoC::Controller *> controllers;
        std::map<std::string, MosaModule *> imports;

        Mosasaurus::MosaContext *context = 0;

    protected:
        void import(std::map<std::string, MosaModule *> imports, std::map<std::string, IoC::Injectable *> services, std::map<std::string, IoC::Controller *> controllers);
        void import(std::map<std::string, IoC::Injectable *> services, std::map<std::string, IoC::Controller *> controllers);
        void registerInjectables(std::map<std::string, IoC::Injectable *> services, std::map<std::string, IoC::Controller *> controllers);
    };

};

#endif