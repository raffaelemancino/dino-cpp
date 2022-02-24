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

        std::map<std::string, IoC::Injectable *> exportedServices;
        std::map<std::string, MosaModule *> exportedModules;

    protected:
        MosaModule();
        void registerInjectables();

        template <class T>
        void addService(std::string name)
        {
            if (std::is_base_of<IoC::Injectable, T>::value)
            {
                IoC::Injectable *service = new T();
                this->services.insert(std::make_pair(name, service));
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
                this->controllers.insert(std::make_pair(name, controller));
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
                this->imports.insert(std::make_pair(name, mosaModule));
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
        template <class T>
        T *inject(std::string name)
        {
            IoC::Injectable *value = 0;
            value = this->services[name];
            if (!value)
            {
                for (const auto &module : this->imports)
                {
                    value = module.second->injectForModuleParent<T>(name);
                    if (value)
                        return (T *)value;
                }
                if (!value)
                    throw std::runtime_error("Injectable reference not foud");
            }

            return (T *)value;
        };

        template <class T>
        T *injectForModuleParent(std::string name)
        {
            IoC::Injectable *service;
            service = this->exportedServices[name];
            if (!service)
            {
                for (const auto &module : this->exportedModules)
                {
                    service = module.second->injectForModuleParent<T>(name);
                    if (service)
                        return (T *)service;
                }
            }
            return (T *)service;
        }
    };

};

#endif