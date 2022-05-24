#include <iostream>
#include <map>

#include "dino/dino.hpp"

#include "dino/recursion/ddfs.hpp"

#include "app.module.hpp"

using namespace std;

int main()
{
    Dino::App *application = Dino::App::getInstance();
    application->bootstrap<AppModule>();
    application->bind(8080, "api");
}