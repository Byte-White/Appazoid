// Appazoid.cpp : Defines the entry point for the application.
//
#include "Appazoid/Appazoid.h"
#include <fstream>

class MainLayer : public az::Layer
{
	std::string readmefile_text = "Failed reading from \'README.md\'";
public:
	MainLayer()
	{
		std::ifstream readmefile;
		readmefile.open("README.md");

		if (readmefile.is_open())
		{
			std::stringstream buffer;
			buffer << readmefile.rdbuf();
			readmefile_text = buffer.str();
			readmefile.close();
		}
	}

	void OnConstruction() override
	{

	}

	void OnEvent(az::Event& e) override
	{
		az::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<az::KeyReleasedEvent>(AZ_BIND_EVENT_FN(OnKeyReleased));
	}

	bool OnKeyReleased(az::KeyReleasedEvent& e)
	{	
		if (e.GetKeyCode() == az::Key::Escape)
		{
			//... do something ...
			APPAZOID_DEBUG("\'ESC\' Got Released");
		}
		return false;
	}

	void OnUIRender() override
	{
		ImGui::Begin("README.md Window");
		ImGui::TextWrapped(readmefile_text.c_str());
		ImGui::End();

		//Status 
		static bool show_info = true;
		static bool show_col_editor = false;
		static bool show_demo = false;
		ImGui::Begin("Status");
		ImGui::Checkbox("show info", &show_info);
		ImGui::SameLine();
		ImGui::Checkbox("show color editor", &show_col_editor);
		ImGui::Checkbox("show demo", &show_demo);
		if(show_demo)
			ImGui::ShowDemoWindow(&show_demo);
		if (show_info)
		{
			ImGui::Text("Delta Time: %f", ImGui::GetIO().DeltaTime);
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "Framerate: %.2f", ImGui::GetIO().Framerate);
		}

		if (show_col_editor)
		{
			ImGui::Begin("Color Editor");
			az::app->window_style.ColorEditor();
			ImGui::End();
		}
		ImGui::End();

	}
};

class MyApplication :public az::Application
{
public:
	MyApplication()
	{
		az::WindowStyle style;
		style.size = az::GetMonitorResolution() - 500;
		//style.monitor = glfwGetPrimaryMonitor(); //Fullscreen
		style.title = "Appazoid Application";
		style.stylecolor = az::StyleColor::StyleColorDark;

		//Enable Flags
		AddConfigFlagCallback([](ImGuiIO& io)
			{
				az::EnableConfigFlag(io, ImGuiConfigFlags_DockingEnable);
				az::EnableConfigFlag(io, ImGuiConfigFlags_NavEnableKeyboard);
				//az::EnableConfigFlag(io,ImGuiConfigFlags_ViewportsEnable);//Errors when using viewports
			});
		//Menu Callback
		
		AddMenubarCallback(AZ_BIND_CALLBACK_FN(MenubarCallback));
		AddLayer<MainLayer>("main_layer");
		#ifdef PRINT_INFORMATION
		az::AppazoidSpecification::Print();
		az::MemoryTracker::Print();
		#endif
		Create(style);
	}
	void MenubarCallback()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))this->Close();
			ImGui::EndMenu();
		}
	}
};


az::Application* az::CreateApplication(int argc, char** argv)
{
	return new MyApplication();
}