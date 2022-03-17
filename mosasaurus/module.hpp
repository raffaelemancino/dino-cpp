#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "models.hpp"

namespace Mosasaurus
{
    class MosaApp;

    class MosaModule
    {
    private:
        MosaModule *parentModule = nullptr;
        std::map<std::string, IoC::Injectable *> services;
        std::map<std::string, IoC::Controller *> controllers;
        std::map<std::string, MosaModule *> imports;

        std::map<std::string, IoC::Injectable *> exportedServices;
        std::map<std::string, MosaModule *> exportedModules;

        void registerController(IoC::Controller *);

    protected:
        MosaModule();

        template <class T>
        void addService(std::string name)
        {
            if (std::is_base_of<IoC::Injectable, T>::value)
            {
                IoC::Injectable *service = new T();
                this->services[name] = service;
                std::cout << "Adding service: " << name << std::endl;
                service->setContext(this);
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
                this->controllers[name] = controller;
                std::cout << "Adding controller: " << name << std::endl;
                controller->setContext(this);
            }
            else
            {
                std::cout << "Controller " << name << " is not Injectable" << std::endl;
            }
        }

        template <class T>
        void addModule(std::string name)
        {
            if (std::is_base_of<MosaModule, T>::value)
            {
                MosaModule *mosaModule = new T();
                mosaModule->setParentModule(this);
                this->imports[name] = mosaModule;
                std::cout << "Adding module: " << name << std::endl;
            }
            else
            {
                std::cout << name << " is not a Module" << std::endl;
            }
        }

        void addExportService(std::string name);
        void addExportModule(std::string name);

    public:
        /**
         * Inject service searching in self module and in child modules
         */
        template <class T>
        T *inject(std::string name)
        {
            IoC::Injectable *value = nullptr;
            try
            {
                value = this->services.at(name);
            }
            catch (std::exception &e)
            {
            }

            if (value)
                return (T *)value;

            if (this->parentModule)
            {
                value = this->parentModule->injectForModuleChild<T>(name);
                if (value)
                    return (T *)value;
            }

            for (const auto &module : this->imports)
            {
                value = module.second->injectForModuleParent<T>(name);
                if (value)
                    return (T *)value;
            }

            if (value)
                return (T *)value;

            throw std::runtime_error("Injectable reference not foud for \"" + name + "\"");
        };

        /**
         *  Serach if child module have a serice
         */
        template <class T>
        T *injectForModuleParent(std::string name)
        {
            IoC::Injectable *service = nullptr;
            try
            {
                service = this->exportedServices.at(name);
            }
            catch (const std::exception &e)
            {
            }
            if (service)
                return (T *)service;

            for (const auto &module : this->exportedModules)
            {
                service = module.second->injectForModuleParent<T>(name);
                if (service)
                    return (T *)service;
            }
            return (T *)service;
        }

        /**
         *  Search if parent module have a service
         */
        template <class T>
        T *injectForModuleChild(std::string name)
        {
            IoC::Injectable *value = nullptr;
            try
            {
                value = this->services.at(name);
            }
            catch (const std::exception &e)
            {
            }

            if (value)
                return (T *)value;

            if (this->parentModule)
            {
                value = this->parentModule->injectForModuleChild<T>(name);
            }

            return (T *)value;
        }

        /**
         *  Set its partend module for service search
         */
        void setParentModule(MosaModule *);

        /**
         *  Compulsory function to avoid IoC in module
         */
        void registerInjectables();
    };

};