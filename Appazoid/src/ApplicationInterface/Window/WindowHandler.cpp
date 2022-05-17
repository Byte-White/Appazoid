#include "WindowHandler.h"
#include "Logging/Log.h"

namespace az 
{


	WindowHandler::WindowHandler(const WindowStyle& style)
	{
		window = glfwCreateWindow(style.width, style.height, style.title.c_str(),
			style.monitor,//WINDOW OR FULLSCREEN MODE
			NULL);
		this->style = style;
		
	}

	WindowHandler::~WindowHandler()
	{
		if(!window_is_destroyed)
			DestroyWindow();
	}
	void WindowHandler::DestroyWindow()
	{
		glfwDestroyWindow(window);
		window_is_destroyed = true;
		APPAZOID_WARN("Window {0} DESTROYED!",style.title);
		
	}

	void WindowHandler::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

}