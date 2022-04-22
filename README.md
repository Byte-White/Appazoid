# Appazoid
C++ GUI Library

######
## How to use:

### How to add repository:
```
git clone --recursive https://github.com/FunhuninjaStudio/Appazoid
```
### CMake stuff:
```CMAKE
add_subdirectory(Appazoid)
target_link_libraries(${PROJECT_NAME} appazoid::appazoid)
```
### C++ Example Code:


```C++
#include "Appazoid/Appazoid.h"

class MainWidget: public az::Widget // Create A Widget SubClass
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
	Application::WindowStyle style; // Create A Window Style
	style.width  = 800;
	style.height = 400;
	style.title  = "Appazoid Application";
	style.stylecolor = style.StyleColorDark;
	Application* app = new Application(style); // Create a window
	app->AddMenubarCallback([app]() // Create a menu
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))app->Close();
				ImGui::EndMenu();
			}
		}
	);
	app->AddWidget<MainWidget>("first_widget", "my window"); // Add a widget
	app->AddWidget<MainWidget>("second_widget", "not my window"); // Add a widget
  
  // Print all widgets
	for (auto& i : app->GetWidgetList())
	{
		std::cout << i.first << " ";
	}
	return app;
}
```
