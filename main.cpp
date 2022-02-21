#include <iostream>
#include <map>

#include "mosasaurus/app.hpp"

#include "app.module.hpp"

using namespace std;

int main()
{
    Mosasaurus::MosaApp *application = Mosasaurus::MosaApp::getInstance();
    application->bootstrap<AppModule>();
}