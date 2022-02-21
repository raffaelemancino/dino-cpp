#include "module.hpp"

using namespace Mosasaurus;

MosaModule::MosaModule()
{
    this->context = new Mosasaurus::MosaContext();
}

void MosaModule::registerInjectables()
{
    for (const auto &service : this->services)
    {
        service.second->onLoadEnd();
    }

    for (const auto &controller : this->controllers)
    {
        controller.second->onLoadEnd();
    }
}