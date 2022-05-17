// Appazoid.cpp : Defines the entry point for the application.
//
#include "Appazoid/Appazoid.h"
#include "Core/AppazoidSpecification.h"
//#include <filesystem>

/// INCLUDECUSTOM WIDGETS
#include"widgets/FrameBufferWidget.h"
///

int z = 0;
class MainWidget : public az::Widget
{
	std::string name;
	std::unique_ptr<az::Image> img;
	//std::unique_ptr<az::WindowHandler> win;
public:
	MainWidget(const std::string& name)
		:name(name)
	{
		//win = std::make_unique<az::WindowHandler>(az::WindowStyle(555, 555));
	}

	void OnConstruction() override
	{
		img = std::make_unique<az::Image>("D:/Files/MG/img/" + name + ".PNG");
	}

	void OnRender() override
	{
		ImGui::Begin(name.c_str());
		//img->Bind(z);
		//if (z == 0)z = 1;
		//else z = 0;
		//img->Bind(0);
		ImGui::ImageButton((void*)img->GetTextureID(), {(float)img->GetWidth(),(float)img->GetHeight()});
		ImGui::Text("Appazoid Test Project");
		ImGui::Text("Framerate: %.2f", ImGui::GetIO().Framerate);
		ImGui::End();

		//win->SwapBuffers();
	}
private:

};


class ContentBrowser : public az::Widget
{
	std::string m_folder_path;
	std::unique_ptr<az::Image> img;
public:
	ContentBrowser(const std::string& folder_path)
		:m_folder_path(folder_path)
	{
	}
	void OnConstruction()
	{

		img = std::make_unique<az::Image>("D:/Files/logo.jpg");
	}
	~ContentBrowser()
	{
	}

	void OnRender() override
	{
		ImGui::Begin(m_folder_path.c_str());
		//for()
		ImGui::Button("TODO: make a content browser.");

		static int sz[2] = { img->GetWidth(),img->GetHeight() };
		ImGui::SliderInt2("size:", sz, 24, 1024);
		ImGui::Image((void*)(img->GetTextureID()), { (float)sz[0],(float)sz[1] });
		ImGui::End();
	}
	void OnImGuiRender() override
	{
	}
private:

};



void ConfigFlags(ImGuiIO& io)
{
	az::EnableConfigFlag(io, ImGuiConfigFlags_DockingEnable);
	az::EnableConfigFlag(io, ImGuiConfigFlags_NavEnableKeyboard);
	//az::EnableConfigFlag(io,ImGuiConfigFlags_ViewportsEnable);
}


az::Application* az::CreateApplication(int argc, char** argv)
{

	az::WindowStyle style;
	style.size = GetMonitorResolution();
	style.monitor = glfwGetPrimaryMonitor();
	style.title = "Appazoid Application";
	style.stylecolor = az::StyleColor::CustomStyleColors;
	Application* app = new Application(style);
	app->AddConfigFlagCallback(ConfigFlags);
	app->AddMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))app->Close();
				ImGui::EndMenu();
			}
		}
	);
	app->AddWidget<MainWidget>("first_widget", "my window");
	app->AddWidget<MainWidget>("second_widget", "not my window");
	app->AddWidget<ContentBrowser>("content_browser","D:/Files/");
	//app->AddWidget<MFrameBuffer>("framebuffer_widget", "FrameBuffer");//TODO: Fix The Errors
	az::AppazoidSpecification::Print();
	for (auto& i : app->GetWidgetList())
	{
		std::cout << i.first << " ";
	}
	std::cout << std::endl;
	//app->HideWidget("first_widget");
	//std::shared_ptr<MainWidget> w2 = std::make_shared<MainWidget>();
	//app->AddWidget(w2);
	return app;
}
//TODO: Test all functions