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

#pragma once

#include "app.hpp"
#include "injectable.hpp"

namespace Dino
{
    class Module
    {
    private:
        Module *parentModule = nullptr;
        std::map<std::string, IoC::Injectable *> services;
        std::map<std::string, IoC::Controller *> controllers;
        std::map<std::string, Module *> imports;

        std::map<std::string, IoC::Injectable *> exportedServices;
        std::map<std::string, Module *> exportedModules;

        IoC::Injectable *inject(std::string);

    protected:
        Module();

        template <class T>
        void addService(std::string name)
        {
            if (std::is_base_of<IoC::Injectable, T>::value)
            {
                IoC::Injectable *service = new T();
                service->name = name;
                this->addService(service);
            }
            else
            {
                std::cout << "Service " << name << " is not Injectable" << std::endl;
            }
        }

        template <class T>
        void addController(std::string name)
        {
            if (std::is_base_of<IoC::Controller, T>::value)
            {
                IoC::Controller *controller = new T();
                controller->name = name;
                this->addController(controller);
            }
            else
            {
                std::cout << "Controller " << name << " is not Injectable" << std::endl;
            }
        }

        template <class T>
        void addModule(std::string name)
        {
            if (std::is_base_of<Module, T>::value)
            {
                Module *module = new T();
                module->name = name;
                this->addModule(module);
            }
            else
            {
                std::cout << name << " is not a Module" << std::endl;
            }
        }

        void addExportService(std::string name);
        void addExportModule(std::string name);

        void addController(IoC::Controller *);
        void addService(IoC::Injectable *);
        void addModule(Module *);

    public:
        std::string name = "";

        /**
         * Inject service searching in self module and in child modules
         */
        template <class T>
        T *inject(std::string name)
        {
            return (T *)this->inject(name);
        };

        /**
         *  Serach if child module have a serice
         */
        IoC::Injectable *injectForModuleParent(std::string name);

        /**
         *  Search if parent module have a service
         */
        IoC::Injectable *injectForModuleChild(std::string);

        /**
         *  Set its partend module for service search
         */
        void setParentModule(Module *);

        /**
         *  Compulsory function to avoid IoC in module
         */
        void registerInjectables();

        /**
         *  After server start register controllers and apis
         */
        void registerControllers();
    };
}