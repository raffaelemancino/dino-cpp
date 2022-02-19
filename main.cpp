#include <iostream>

#include "mosasaurus/ioc.hpp"
#include "mosasaurus/app.hpp"

using namespace std;

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
};

int main()
{
    Mosasaurus::App *application = new Mosasaurus::App();
    cout << "Hello world" << endl;

    map<string, IoC::Injectable *> services;
    services.insert(make_pair("test-service", new Test()));

    application->configure(services);

    Test *testService = (Test *)application->getContext()->inject("test-service");
    testService->setA(5);
    cout << testService->getA() << endl;

    Test *testService2 = (Test *)application->getContext()->inject("test-service");
    testService2->setA(10);
    cout << testService2->getA() << endl;
    cout << testService->getA() << endl;
}