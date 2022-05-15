#pragma once

#include <map>
#include <string>
#include <iostream>

#include "dino/models.hpp"

#include "submodule.module.hpp"

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
        this->test = this->context->inject<Test>("test-component");
        this->getTestValue();
    }
};

class AppModule : public Dino::Module
{
private:
public:
    AppModule()
    {
        this->addService<RM>("rm-service");
        // this->addService<Test>("test-component");
        // this->addExportService("rm-services");
        this->addModule<SubModule>("submodule");
    }
};