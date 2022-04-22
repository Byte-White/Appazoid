#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

#include "Appazoid/UI/Widget.h"

namespace az {

	//static LPCTSTR windows_title = _T("My App");
	//static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	namespace entrypoint { void Main(int argc, char** argv); }

	class Application
	{
	private:
		int widget_naming_count=0;// helps to make a default name (example: widget_123)
	public:
		bool done;
		float clear_color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
		struct WindowStyle
		{
			int width, height;
			std::string title;
			enum StyleColor
			{
				StyleColorDark=0, StyleColorLight, StyleColorClassic
			}stylecolor = StyleColorDark;
		};
		const WindowStyle window_style;
	public:
		Application(const WindowStyle& style = {255,255,"Appazoid Application"})
			:window_style(style),done(false)
		{};
		~Application();
		void Run();
		/* AddWidget worse function(backup)
		template<typename T>
		inline void AddWidget(const std::shared_ptr<T>& _widget, std::string widget_name)
		{
			this->m_widgets[widget_name] = (std::make_shared<T>());
			
			//Widget(_widget).OnConstruction();
		};
		*/

		template<typename T, typename ...T_args>
		inline void AddWidget(std::string widget_name,T_args&... args)
		{
			if (widget_name == "")widget_name = "widget_"+widget_naming_count;
			static_assert(std::is_base_of<Widget, T>::value, "Added type should be a subclass of az::Widget");
			this->m_widgets[widget_name]=(std::make_shared<T>(args...));
			//->OnConstruction();
		}


		inline std::unordered_map<std::string, std::shared_ptr<Widget>>& GetWidgetList()
		{
			return m_widgets;
		}

		inline void AddMenubarCallback(std::function<void()> function) { m_MenubarCallback = function; }
		inline void Close() { done = true; }
		void HideWidget(std::string widget_name);
		//std::vector<std::string> GetWidgetsNames();
	public:
		std::function<void()> m_MenubarCallback;//menubar callback function pointer
	private:
		//std::vector<std::shared_ptr<Widget>> m_widgets;
		std::unordered_map<std::string,std::shared_ptr<Widget>> m_widgets;//hash map(name:widget)
	};
	//To be defined in CLIENT
	Application* CreateApplication(int,char**);
}
