#include "mosasaurus/module.hpp"
#include "mosasaurus/models.hpp"
#include "app.module.hpp"

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

class SubModule : public Mosasaurus::MosaModule
{
public:
    SubModule()
    {
        this->addService<Test>("test-component");
        this->addExportService("test-component");
        this->registerInjectables();
    }
};