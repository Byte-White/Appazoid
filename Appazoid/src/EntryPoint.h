#pragma once
#include "ApplicationInterface/Application.h"

extern az::Application* az::CreateApplication(int,char**);

#include <stdio.h>
#include <iostream>
#include "Logging/Log.h"


#ifndef AZ_CUSTOM_MAIN
int main(int argc,char** argv)
{
    az::Log::Init();
    az::entrypoint::app = az::CreateApplication(argc,argv);
    APPAZOID_CORE_INFO("Initializing GLFW...");
    az::entrypoint::init_glfw();
    APPAZOID_CORE_INFO("Creating a window...");

    az::entrypoint::create_window();
    APPAZOID_CORE_INFO("Initializing IMGUI...");
    az::entrypoint::init_imgui();

    az::entrypoint::Main(argc,argv);

    APPAZOID_CORE_INFO("Cleaning up...");
    az::entrypoint::cleanup();
    return 0;
}
#endif