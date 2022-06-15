#pragma once
#include "ApplicationInterface/Application.h"

extern az::Application* az::CreateApplication(int,char**);

#include <stdio.h>
#include <iostream>
#include "Logging/Log.h"
#include "Core/MemoryTracker.h"


#include "Core/Input.h"



#ifndef AZ_CUSTOM_MAIN // Define to make a custom main function
int main(int argc,char** argv)
{
    az::Log::Init();// Initialize Logging
    APPAZOID_CORE_INFO("Initializing GLFW...");
    az::entrypoint::init_glfw();

    APPAZOID_CORE_INFO("Creating IMGUI Context...");
    // Create ImGuiContext
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    az::entrypoint::app = az::CreateApplication(argc,argv);// client code will run here
    
    APPAZOID_CORE_INFO("Initializing IMGUI...");
    az::entrypoint::init_imgui();

    az::entrypoint::Main(argc,argv);

    APPAZOID_CORE_INFO("Cleaning up...");
    az::entrypoint::cleanup();
    return 0;
}
#endif