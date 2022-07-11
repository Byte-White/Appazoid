#include "WindowHandler.h"
#include "WindowStyle.h"
#include "Logging/Log.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"


namespace az 
{
	//Error handling
	static void GLFWErrorCallback(int error, const char* description)
	{
		APPAZOID_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	std::string WindowStyle::WindowColors::names[55] =
	{
		std::string("Text"),
		std::string("TextDisabled"),
		std::string("WindowBg"),
		std::string("ChildBg"),
		std::string("PopupBg"),
		std::string("Border"),
		std::string("BorderShadow"),
		std::string("FrameBg"),
		std::string("FrameBgHovered"),
		std::string("FrameBgActive"),
		std::string("TitleBg"),
		std::string("TitleBgActive"),
		std::string("TitleBgCollapsed"),
		std::string("MenuBarBg"),
		std::string("ScrollbarBg"),
		std::string("ScrollbarGrab"),
		std::string("ScrollbarGrabHovered"),
		std::string("ScrollbarGrabActive"),
		std::string("CheckMark"),
		std::string("SliderGrab"),
		std::string("SliderGrabActive"),
		std::string("Button"),
		std::string("ButtonHovered"),
		std::string("ButtonActive"),
		std::string("Header"),
		std::string("HeaderHovered"),
		std::string("HeaderActive"),
		std::string("Separator"),
		std::string("SeparatorHovered"),
		std::string("SeparatorActive"),
		std::string("ResizeGrip"),
		std::string("ResizeGripHovered"),
		std::string("ResizeGripActive"),
		std::string("Tab"),
		std::string("TabHovered"),
		std::string("TabActive"),
		std::string("TabUnfocused"),
		std::string("TabUnfocusedActive"),
		std::string("DockingPreview"),
		std::string("DockingEmptyBg"),
		std::string("PlotLines"),
		std::string("PlotLinesHovered"),
		std::string("PlotHistogram"),
		std::string("PlotHistogramHovered"),
		std::string("TableHeaderBg"),
		std::string("TableBorderStrong"),
		std::string("TableBorderLight"),
		std::string("TableRowBg"),
		std::string("TableRowBgAlt"),
		std::string("TextSelectedBg"),
		std::string("DragDropTarget"),
		std::string("NavHighlight"),
		std::string("NavWindowingHighlight"),
		std::string("NavWindowingDimBg"),
		std::string("ModalWindowDimBg")
	};

	void WindowHandler::SetGLFWCallbacks()
	{
		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowStyle& data = *(WindowStyle*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				//if(data.EventCallback)
					data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowStyle& data = *(WindowStyle*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				//if(data.EventCallback)
					data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowStyle& data = *(WindowStyle*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					//if(data.EventCallback)
						data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					//if(data.EventCallback)
						data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					//if(data.EventCallback)
						data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowStyle& data = *(WindowStyle*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				//if(data.EventCallback)
					data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowStyle& data = *(WindowStyle*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					//if(data.EventCallback)
						data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					//if(data.EventCallback)
						data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowStyle& data = *(WindowStyle*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				//if(data.EventCallback)
					data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowStyle& data = *(WindowStyle*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				//if(data.EventCallback)
					data.EventCallback(event);
			});
	}

	WindowHandler::WindowHandler(const WindowStyle& style)
	{
		m_Window = glfwCreateWindow(style.width, style.height, style.title.c_str(),
			style.monitor,//WINDOW OR FULLSCREEN MODE
			NULL);
		this->style = style;

		Init();
	}

	void WindowHandler::Init()
	{
		glfwSetWindowUserPointer(m_Window, &this->style);
		glfwMakeContextCurrent(m_Window);
		SetVSync(true);
		SetGLFWCallbacks();
	}

	WindowHandler::~WindowHandler()
	{
		if(!window_is_destroyed)
			DestroyWindow();
	}
	void WindowHandler::DestroyWindow()
	{
		glfwDestroyWindow(m_Window);
		window_is_destroyed = true;
		//APPAZOID_WARN("Window {0} DESTROYED!",style.title);
		
	}

	void WindowHandler::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	void WindowHandler::SetVSync(bool enabled)
	{
		Log::CoreInfo(enabled ? "VSync enabled" : "VSync disabled");
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		style.VSync = enabled;
	}

	bool WindowHandler::IsVSync() const
	{
		return style.VSync;
	}
}