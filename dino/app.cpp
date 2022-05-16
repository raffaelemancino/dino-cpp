/*
Copyright (C) 2022 Raffaele Francesco Mancino <raffaelefrancesco.mancino@gmail.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
Boston, MA  02110-1301, USA.
*/

#include "app.hpp"

using namespace Dino;

App *App::app = nullptr;

App::App()
{
    this->startupLogo();
    Logger::getInstance()->log("App init");
}

App *App::getInstance()
{
    if (!app)
    {
        app = new App();
    }
    return app;
}

Mongoose::Server *App::getServerInstance()
{
    if (this->server)
    {
        return this->server;
    }
    else
    {
        std::invalid_argument("Server uninitialized");
        return nullptr;
    }
}

void App::startupLogo()
{
    std::string logo = "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▓░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▓▓▓▓▒░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▓▓▒▒▓▒░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▓▒▒▒▒▓▒░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░▒░░░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░▓▓▒▒▒▒▓▓▒░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░▒▓▓▓░░░▒▒▓▓▓▒░░░░░░░░░░░░░░░░░░▒▓▒▒▒▒▒▒▓▒░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░▒▓▓▓▓▒▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░▒▓▒▒▓▒▒▒▓▒░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░▓▓▓▒░▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░▓▒▒▒▒▒▒▓▓▒░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒░░░░░░░░░░░░░░░░▓▓▒▒▒▒▒▓▓▓▒░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░▒▓▒▒▒▒▒▒▓▒▒▓▒░░░░░░░░░░░░░░▒░░░░\n\
░░░░░░░░▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░▓▓▒▓▒▒▒▒▓▓▓▓▓▓▓▒▒▓▒░▒▓▒▒▓▓▓▓▒░░░\n\
░░░░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒░░░░░░░░░░░░░░░▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░░\n\
░░░░░░▒▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▒░░░░\n\
░░░░░▒▓▓▓▓▓▓▓▓▓▒░░░░░░░░░░░░░░░░░░░░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▒▒▒▒▒▒▒▓▓▒▒░░░░░░░░░\n\
░░░░▒▓▓▓▓▓▓▓▓▒░░░░░░░░░░░░░░░░░░░░▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▓▓▓▒░░░░░░░░░░░░░\n\
░░░▒▓▓▓▓▓▓▓▓▒░░░░░░░░░░░░░░░░░░░░░▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▒░░░░░░░░░░░░░░░░\n\
░░░░▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░░▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░░\n\
░░░▒▓▓▓▓▓▓▓▓▒░░░░░░░░░░░░░░░░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░░\n\
░░░▒▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░\n\
░░░░▒▓▓▓▓▓▓▓▓▓░░░░░░░░░░░▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▒▓▒▒▒▒▒▓▓▓▓▓▓▓▓▓▒░░░░░░░░░░░░\n\
░░░░░▓▓▓▓▓▓▓▓▓▓▓▒░░░░▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒░░░░░░░░░░░\n\
░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▓▓▒▒▒▒▒▒▒▒▓▒░░░░░░░░░░░░░░░░\n\
░░░░░░▒▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒░▒▓▒▒▒▒▒▒▒▒▒▓▒░░░░░░░░░░░░░░░\n\
░░░░░░░▒▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▒░░▓▓▓▒▒▒▒▒▒▒▒▒▓▒░░░░░░░░░░░░░░\n\
░░░░░░░░▒▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▒░░▒▓▒░░▒▓▓▒▒▒▒▒▒▓▓░░░░░░░░░░░░░░\n\
░░░░░░░░░░▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▒▒░░░░▒▓▒░░░░░░░▒▓▓▒▒▒▒▓░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░▒▓▓▓▓▓▓▓▒▒▒▓▓▓▓▓▓▓▓▓▒░░░░░░░▒▓▒░░░░░░░░░░░▒▓▓▒▒▓░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░▒▒▓▓▒▒▒▒▒▒▒▒▓▒░░░░░░░░░░▒▒▓▓▒░░░░░░░░░░░░░░░░░▒▓▓░░░░░░░░░░░░░░\n\
░░░░░░░░░░▒▓▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░░░░░░░░░░░▒░░░░░░░░░░░░░░\n\
░░░░░░░▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▓▒░░▒▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\
░░░░░▒▓▓▒▒▒▒▒▒▒▒▒▒▒▓▓▒░░░░▓▓▓▓▓▓▓▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░▒▒▓▓▓▓▓▓▒▒▒░░░░░░░▓▓▓▓▓▓▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░░░░░░░░░░▓▓▓▓▓▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░░░░░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";

    std::string name = "  _____  _                                   \n\
 |  __ \\(_)                        _     _   \n\
 | |  | |_ _ __   ___ ______ ___ _| |_ _| |_ \n\
 | |  | | | '_ \\ / _ \\______/ __|_   _|_   _|\n\
 | |__| | | | | | (_) |    | (__  |_|   |_|  \n\
 |_____/|_|_| |_|\\___/      \\___|            \n\
                                             \n\
                            C++ Modern Web Framework";
    std::cout << logo << std::endl;
    std::cout << name << std::endl;
}

void App::bind(int port, std::string baseUrl = "www")
{
    this->server = new Mongoose::Server(port, baseUrl.c_str());
    this->server->start();
    Logger::getInstance()->log("Server started at port " + to_string(port) + " with base name /" + baseUrl);
    Logger::getInstance()->log("Loading app API");
    this->bootstrapModule->registerControllers();
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void App::bootstrap(Module *m)
{
    m->name = "boot_module";
    this->bootstrapModule = m;
    this->bootstrapModule->registerInjectables();
    Logger::getInstance()->log("App configuration End");
}