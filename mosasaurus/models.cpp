#include "module.hpp"

using namespace IoC;

void Injectable::setContext(Mosasaurus::MosaContext *c)
{
    this->context = c;
}