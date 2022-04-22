// Appazoid.cpp : Defines the entry point for the application.
//

#include "Appazoid/Appazoid.h"
//#include <filesystem>

class MainWidget: public az::Widget
{
	std::string name;
public:
	MainWidget(const std::string& name)
		:name(name)
	{

	}

	void OnRender() override
	{
		ImGui::Begin(name.c_str());
		ImGui::Text("Appazoid Test Project");
		ImGui::End();
	}
private:

};

class ContentBrowser : public az::Widget
{
	std::string m_folder_path;
public:
	ContentBrowser(const std::string& folder_path)
		:m_folder_path(folder_path)
	{

	}

	void OnRender() override
	{
		ImGui::Begin(m_folder_path.c_str());
		//for()
		ImGui::Button("TODO: make a content browser");
		ImGui::End();
	}
private:

};



az::Application* az::CreateApplication(int argc,char**argv)
{
	Application::WindowStyle style;
	style.width  = 800;
	style.height = 400;
	style.title  = "Appazoid Application";
	style.stylecolor = style.StyleColorDark;
	Application* app = new Application(style);
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
	app->AddWidget<ContentBrowser>("content_browser","D:/Files/random");
	for (auto& i : app->GetWidgetList())
	{
		std::cout << i.first << " ";
	}
	//app->HideWidget("first_widget");
	//std::shared_ptr<MainWidget> w2 = std::make_shared<MainWidget>();
	//app->AddWidget(w2);
	return app;
}
//TODO: Test all functions