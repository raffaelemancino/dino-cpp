#include "module.hpp"

using namespace Dino;

Module::Module()
{
}

void Module::addController(IoC::Controller *controller)
{
    this->controllers[controller->name] = controller;
    std::cout << "Adding controller: " << controller->name << std::endl;
    controller->setContext(this);
}

void Module::addService(IoC::Injectable *service)
{
    this->services[service->name] = service;
    std::cout << "Adding service: " << service->name << std::endl;
    service->setContext(this);
}

void Module::addModule(Module *m)
{
    m->setParentModule(this);
    this->imports[m->name] = m;
    std::cout << "Adding module: " << name << std::endl;
}

void Module::registerControllers()
{
    for (const auto &controller : this->controllers)
    {
        controller.second->registerApi();
        Dino::App::getInstance()->getServerInstance()->registerController(controller.second);
    }

    for (auto &module : this->imports)
    {
        module.second->registerControllers();
    }
}

void Module::registerInjectables()
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

void Module::addExportService(std::string name)
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

void Module::addExportModule(std::string name)
{
    Dino::Module *module = nullptr;
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

void Module::setParentModule(Module *module)
{
    this->parentModule = module;
}

IoC::Injectable *Module::inject(std::string name)
{
    IoC::Injectable *value = nullptr;
    try
    {
        value = this->services.at(name);
        return value;
    }
    catch (std::exception &e)
    {
    }

    if (this->parentModule)
    {
        value = this->parentModule->injectForModuleChild(name);
        if (value)
            return value;
    }

    for (const auto &module : this->imports)
    {
        value = module.second->injectForModuleParent(name);
        if (value)
            return value;
    }

    if (value)
        return value;

    throw std::runtime_error("Injectable reference not foud for \"" + name + "\"");
}

IoC::Injectable *Module::injectForModuleChild(std::string name)
{
    IoC::Injectable *value = nullptr;
    try
    {
        value = this->services.at(name);
        return value;
    }
    catch (const std::exception &e)
    {
    }

    if (this->parentModule)
    {
        value = this->parentModule->injectForModuleChild(name);
    }

    return value;
}

IoC::Injectable *Module::injectForModuleParent(std::string name)
{
    IoC::Injectable *service = nullptr;
    try
    {
        service = this->exportedServices.at(name);
        return service;
    }
    catch (const std::exception &e)
    {
    }

    for (const auto &module : this->exportedModules)
    {
        service = module.second->injectForModuleParent(name);
        if (service)
            return service;
    }
    return service;
}