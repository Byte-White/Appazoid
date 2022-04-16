// Appazoid.cpp : Defines the entry point for the application.
//

#include "Appazoid/Appazoid.h"
#include <iostream>

class Sandbox : public az::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
	void Run() override
	{

	}
};

az::Application* az::CreateApplication()
{
	return new Sandbox();
}