#include "module.hpp"

using namespace Mosasaurus;

void MosaModule::import(std::map<std::string, MosaModule *> imports, std::map<std::string, IoC::Injectable *> services, std::map<std::string, IoC::Controller *> controllers)
{
    this->context = new Mosasaurus::MosaContext();
    this->imports = imports;

    this->registerInjectables(services, controllers);
}

void MosaModule::import(std::map<std::string, IoC::Injectable *> services, std::map<std::string, IoC::Controller *> controllers)
{
    this->context = new Mosasaurus::MosaContext();
    std::cout << "No imports provided" << std::endl;

    this->registerInjectables(services, controllers);
}

void MosaModule::registerInjectables(std::map<std::string, IoC::Injectable *> services, std::map<std::string, IoC::Controller *> controllers)
{
    this->services = services;
    this->controllers = controllers;

    for (const auto &service : services)
    {
        this->context->addMapContext(service.first, service.second);
        std::cout << "Adding service: " << service.first << std::endl;
        service.second->setContext(this->context);
    }

    for (const auto &controller : controllers)
    {
        std::cout << "Adding controller: " << controller.first << std::endl;
        controller.second->setContext(this->context);
    }

    for (const auto &service : services)
    {
        service.second->onLoadEnd();
    }

    for (const auto &controller : controllers)
    {
        controller.second->onLoadEnd();
    }
}