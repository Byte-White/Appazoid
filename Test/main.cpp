// Appazoid.cpp : Defines the entry point for the application.
//
#include "Appazoid/Appazoid.h"

//#include <filesystem>

/// INCLUDE CUSTOM WIDGETS
#include"widgets/FrameBufferWidget.h"
///

//int z = 0;
class MainLayer : public az::Layer
{
	std::string name;
	std::unique_ptr<az::Image> img;
	//std::unique_ptr<az::WindowHandler> win;
public:
	MainLayer(const std::string& name)
		:name(name)
	{
		//win = std::make_unique<az::WindowHandler>(az::WindowStyle(555, 555));
	}

	void OnConstruction() override
	{
		img = std::make_unique<az::Image>("D:/Files/MG/img/" + name + ".PNG");//TODO: Add exceptions and dont crash when an image is not found.
	}

	void OnUIRender() override
	{
		ImGui::Begin(name.c_str());

		//img->Bind(z);
		//if (z == 0)z = 1;
		//else z = 0;
		//img->Bind(0);
		ImGui::ImageButton(*img, {(float)img->GetWidth(),(float)img->GetHeight()});
		ImGui::Text("Appazoid Test Project");
		ImGui::Text("Framerate: %.2f", ImGui::GetIO().Framerate);
		ImGui::End();

		//win->SwapBuffers();
	}
private:

};


class ContentBrowser : public az::Layer
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

	void OnUIRender() override
	{
		ImGui::Begin(m_folder_path.c_str());
		//for()
		ImGui::Button("TODO: make a content browser.");

		static int sz[2] = { img->GetWidth(),img->GetHeight() };
		ImGui::SliderInt2("size:", sz, 24, 1024);
		ImGui::Image(*img, glm::ivec2(sz[0],sz[1]));
		//ImGui::Image((void*)(img->GetTextureID()), { (float)sz[0],(float)sz[1] });
		
		ImGui::End();
	}
	void OnBufferSwap() override
	{
	}
private:

};

class TestLayer: public az::Layer
{
public:
	TestLayer()
	{

	}
	void OnConstruction() override
	{

	}
	void OnDestruction() override
	{

	}
	void OnUIRender() override
	{
		ImGui::Begin("Hello World");
		ImGui::PushItemWidth(500);
		ImGui::TextColored(ImVec4(255, 0, 0, 1), "Hi There!");
		ImGui::SetCursorPosY(ImGui::GetWindowSize().y-200);
		//ImGui::SameLine();
		ImGui::TextColored(ImVec4(0, 255, 0, 1), "Hi There!");
		ImGui::TextColored(ImVec4(0, 0, 255, 1), "Hi There!");
		ImGui::End();
	}
};

void ConfigFlags(ImGuiIO& io)
{
	az::EnableConfigFlag(io, ImGuiConfigFlags_DockingEnable);
	az::EnableConfigFlag(io, ImGuiConfigFlags_NavEnableKeyboard);
	//az::EnableConfigFlag(io,ImGuiConfigFlags_ViewportsEnable);//Errors when using viewports
}


az::Application* az::CreateApplication(int argc, char** argv)
{

	az::WindowStyle style;
	style.size = GetMonitorResolution()-500;
	//style.monitor = glfwGetPrimaryMonitor();
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
	app->AddOverlay<TestLayer>("test_layer");
	app->AddLayer<MainLayer>("first_layer", "my window");
	app->AddLayer<MainLayer>("second_layer", "not my window");
	app->AddLayer<ContentBrowser>("content_browser","D:/Files/");
	//app->AddLayer<MFrameBuffer>("framebuffer_widget", "FrameBuffer");//TODO: Fix The Errors
	az::AppazoidSpecification::Print();
	az::MemoryTracker::Print();
	for (auto& i : app->GetLayerStack())
	{

		std::cout << i.first << " ";
	}
	std::cout << std::endl;
	//app->HideLayer("first_widget");
	//std::shared_ptr<MainLayer> w2 = std::make_shared<MainLayer>();
	//app->AddLayer(w2);
	return app;
}