# Appazoid [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
C++ GUI Framework
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl) 
![vk_badge](https://user-images.githubusercontent.com/51212450/178277240-37ccc926-1444-4fff-812b-48764b33536d.png)

# "Byte Engine" - A C++ Game Engine Made With Appazoid
![byteengine](https://user-images.githubusercontent.com/51212450/178272164-844eea45-7513-4d7b-ab59-d9e5b2f26a1a.png)
## How to use:
# REQUIREMENTS:
Build System Generator : ![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

Vulkan SDK (Optional)

IDE: ![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white) (Optional, Recommended)


#Test Project

https://github.com/Byte-White/Appazoid-Test

### Downloading the repository:
```
git clone --recursive https://github.com/Byte-White/Appazoid
```
If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.
### CMake:
```CMAKE
add_subdirectory(Appazoid)
target_link_libraries(${PROJECT_NAME} appazoid::appazoid)
```
Add `add_compile_definitions(AZ_RENDER_API=AZ_RENDER_API_OPENGL)` to use
OpenGL as render api and `add_compile_definitions(AZ_RENDER_API=AZ_RENDER_API_VULKAN)`
for Vulkan
### C++ Example Code:


```C++
#include "Appazoid/Appazoid.h"


class MainLayer : public az::Layer
{

public:
	MainLayer()
	{

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
		ImGui::Begin("Main Window");
		ImGui::Text("Hello World!");
		ImGui::Button("Hi There!");
		ImGui::End();

		//Status 
		static bool show_info = true;
		static bool show_col_editor = false;

		ImGui::Begin("Status");
		ImGui::Checkbox("show info", &show_info);
		ImGui::SameLine();
		ImGui::Checkbox("show color editor", &show_col_editor);
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
		az::AppazoidSpecification::Print();
		az::MemoryTracker::Print();
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
```
