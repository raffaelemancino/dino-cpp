#include "models.hpp"

using namespace IoC;

void Injectable::setContext(Dino::Module *c)
{
    this->context = c;
}