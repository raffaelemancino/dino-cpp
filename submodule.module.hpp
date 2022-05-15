#pragma once

#include "dino/models.hpp"
#include "app.module.hpp"

#include <iostream>

class RM;

class Test : public IoC::Component
{
private:
    int a = 0;
    RM *rm = nullptr;

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
        this->rm = this->context->inject<RM>("rm-service");
    }
};

class TC : public IoC::RestController
{
public:
    void registerApi()
    {
        cout << "TC controller register api" << endl;
    }
};

class SubModule : public Dino::Module
{
public:
    SubModule()
    {
        this->addService<Test>("test-component");
        this->addExportService("test-component");
        this->addController<TC>("test-controller");
    }
};