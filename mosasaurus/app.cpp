#include "app.hpp"

using namespace Mosasaurus;

App::App()
{
    std::cout << "App Init" << std::endl;
    this->context = IoC::Context::getInstance();
}

App::~App()
{
}

App::App(const App &app)
{
}

void App::configure(std::map<std::string, IoC::Injectable *> injectables)
{
    std::cout << "App configuration" << std::endl;
    for (const auto &injectable : injectables)
    {
        std::cout << "Creating Service \"" << injectable.first << "\"" << std::endl;
        this->context->addMapContext(injectable.first, injectable.second);
    }
}

IoC::Context *App::getContext()
{
    return this->context;
}