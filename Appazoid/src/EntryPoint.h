#pragma once
#include "ApplicationInterface/Application.h"

extern az::Application* az::CreateApplication();

int main()
{
	auto app = az::CreateApplication();

	app->Run();
	
	delete app;
}