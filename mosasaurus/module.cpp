#include "module.hpp"
#include "app.hpp"

using namespace Mosasaurus;

MosaModule::MosaModule()
{
}

void MosaModule::registerController(IoC::Controller *controller)
{
    Mosasaurus::MosaApp *appTmp = Mosasaurus::MosaApp::getInstance();
    appTmp->getServerInstance()->registerController(controller);
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

    for (auto &module : this->imports)
    {
        module.second->registerInjectables();
    }
}

void MosaModule::addExportService(std::string name)
{
    IoC::Injectable *service = nullptr;
    service = this->services[name];
    if (service)
    {
        this->exportedServices[name] = service;
    }
    else
    {
        throw std::runtime_error("No service with name: " + name + " can be exported");
    }
}

void MosaModule::addExportModule(std::string name)
{
    Mosasaurus::MosaModule *module = nullptr;
    module = this->imports[name];
    if (module)
    {
        this->exportedModules[name] = module;
    }
    else
    {
        throw std::runtime_error("No module with name: " + name + " can be exported");
    }
}

void MosaModule::setParentModule(MosaModule *module)
{
    this->parentModule = module;
}