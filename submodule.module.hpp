#include "mosasaurus/module.hpp"
#include "mosasaurus/models.hpp"
#include "app.module.hpp"

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
};

class SubModule : public Mosasaurus::MosaModule
{
public:
    SubModule()
    {
        this->addService<Test>("test-component");
        this->addExportService("test-component");
        this->addController<TC>("test-controller");
    }
};