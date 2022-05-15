#include <iostream>
#include <map>

#include "dino/mosasaurus.hpp"

#include "app.module.hpp"

using namespace std;

int main()
{
    Dino::MosaApp *application = Dino::MosaApp::getInstance();
    application->bootstrap<AppModule>();
    application->bind(8080, "api");
}