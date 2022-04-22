#include "Application.h"
#include "imgui.h"
namespace az {
	
	Application::~Application()
	{

	}
	
	 void ApplicationMain()
	 {

	 }

	void Application::Run()
	{
		//menubar
		if (m_MenubarCallback)
		{
			if (ImGui::BeginMenuBar())
			{
				m_MenubarCallback();
				ImGui::EndMenuBar();
			}
		}
		//render each widget
		for (auto& widget : m_widgets)
		{
			if(widget.second->visible)
				widget.second->OnRender();
		}
	}

	void Application::HideWidget(std::string widget_name)
	{
		if(m_widgets.find(widget_name)!=m_widgets.end())
			this->m_widgets[widget_name]->visible = false;
	}

}