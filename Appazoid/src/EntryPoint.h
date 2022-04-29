#pragma once
#include "ApplicationInterface/Application.h"

extern az::Application* az::CreateApplication(int,char**);

#include <stdio.h>
#include <iostream>


/*static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}*/
#ifndef AZ_CUSTOM_MAIN
int main(int argc,char** argv)
{
    az::entrypoint::app = az::CreateApplication(argc,argv);

    az::entrypoint::init_glfw();

    az::entrypoint::create_window();
    az::entrypoint::init_imgui();

    az::entrypoint::Main(argc,argv);

    az::entrypoint::cleanup();
    return 0;
}
#endif