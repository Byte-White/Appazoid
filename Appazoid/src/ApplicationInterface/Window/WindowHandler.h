#pragma once
#include "GLFW/glfw3.h"
#include "WindowStyle.h"

namespace az 
{

	class WindowHandler
	{
		bool window_is_destroyed = false;
	public:
		WindowHandler(const WindowStyle& style);
		~WindowHandler();
		inline GLFWwindow* GetGLFWWindow() { return window; }
		inline WindowStyle& GetWindowStyle() { return style; }
		void SwapBuffers();
		void DestroyWindow();
	private:
		GLFWwindow* window;
		WindowStyle style;
	};

}