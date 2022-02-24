#include "module.hpp"

using namespace IoC;

void Injectable::setContext(Mosasaurus::MosaModule *c)
{
    this->context = c;
}