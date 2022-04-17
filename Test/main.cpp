// Appazoid.cpp : Defines the entry point for the application.
//

#include "Appazoid/Appazoid.h"

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



az::Application* az::CreateApplication(int argc,char**argv)
{
	Application::WindowStyle style;
	style.width  = 800;
	style.height = 400;
	style.title  = "Appazoid Application";
	Application* app = new Application(style);
	app->AddWidget<MainWidget>("first_widget", "my window");
	app->AddWidget<MainWidget>("second_widget", "not my window");
	//app->HideWidget("first_widget");
	//std::shared_ptr<MainWidget> w2 = std::make_shared<MainWidget>();
	//app->AddWidget(w2);
	return app;
}