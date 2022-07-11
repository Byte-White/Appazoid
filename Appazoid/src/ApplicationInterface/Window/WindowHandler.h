#pragma once
#include "GLFW/glfw3.h"
#include "WindowStyle.h"
#include "Events/Event.h"

namespace az 
{

	class WindowHandler
	{
		bool window_is_destroyed = false;
		void SetGLFWCallbacks();
	public:
		WindowHandler(const WindowStyle& style);
		WindowHandler() = delete;
		void Init();
		~WindowHandler();
		inline GLFWwindow* GetGLFWWindow() { return m_Window; }
		inline WindowStyle& GetWindowStyle() { return style; }
		void SwapBuffers();
		void DestroyWindow();
		inline int GetWidth() { return style.width; }
		inline int GetHeight() { return style.height; }
		void SetEventCallback(const EventCallbackFn& callback) { style.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;
	private:
		GLFWwindow* m_Window;
		WindowStyle style;

	};

}