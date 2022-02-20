#ifndef APPMODULE
#define APPMODULE

#include <map>
#include <string>
#include <iostream>

#include "mosasaurus/module.hpp"
#include "mosasaurus/models.hpp"

class Test : public IoC::Component
{
private:
    int a = 0;

public:
    int getA()
    {
        return this->a;
    }
    void setA(int newA)
    {
        this->a = newA;
    }
    void onLoadEnd()
    {
    }
};

class RM : public IoC::Service
{
private:
    Test *test = 0;

public:
    void getTestValue()
    {
        std::cout << "Value is: " << this->test->getA() << std::endl;
        this->test->setA(5);
        std::cout << "New Value is: " << this->test->getA() << std::endl;
    }
    void onLoadEnd()
    {
        this->test = (Test *)this->context->inject("test-component");
        this->getTestValue();
    }
};

class AppModule : public Mosasaurus::MosaModule
{
private:
public:
    AppModule()
    {
        std::map<std::string, IoC::Injectable *> services;
        services.insert(std::make_pair("test-component", new Test()));
        services.insert(std::make_pair("rm-service", new RM()));

        std::map<std::string, IoC::Controller *> controllers;
        std::map<std::string, Mosasaurus::MosaModule *> imports;
        this->import(services, controllers);
    }
};

#endif