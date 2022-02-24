#include "module.hpp"

using namespace Mosasaurus;

MosaModule::MosaModule()
{
}

void MosaModule::registerInjectables()
{
    for (const auto &service : this->services)
    {
        service.second->onLoadEnd();
    }

    for (const auto &controller : this->controllers)
    {
        controller.second->onLoadEnd();
    }
}

void MosaModule::addExportService(std::string name)
{
    IoC::Injectable *service;
    service = this->services[name];
    if (service)
    {
        this->exportedServices.insert(std::make_pair(name, service));
    }
    else
    {
        throw std::runtime_error("No service with name: " + name + " can be exported");
    }
}

void MosaModule::addExportModule(std::string name)
{
    Mosasaurus::MosaModule *module;
    module = this->imports[name];
    if (module)
    {
        this->exportedModules.insert(std::make_pair(name, module));
    }
    else
    {
        throw std::runtime_error("No module with name: " + name + " can be exported");
    }
}