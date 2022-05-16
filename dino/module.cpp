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

#include "module.hpp"

using namespace Dino;

Module::Module()
{
}

void Module::addController(IoC::Controller *controller)
{
    this->controllers[controller->name] = controller;
    Logger::getInstance()->log("Adding controller: " + controller->name);
    controller->setContext(this);
}

void Module::addService(IoC::Injectable *service)
{
    this->services[service->name] = service;
    Logger::getInstance()->log("Adding service: " + service->name);
    service->setContext(this);
}

void Module::addModule(Module *m)
{
    m->setParentModule(this);
    this->imports[m->name] = m;
    Logger::getInstance()->log("Adding module: " + m->name);
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