// Appazoid.cpp : Defines the entry point for the application.
//
#include "Appazoid/Appazoid.h"
#include "Core/AppazoidSpecification.h"
//#include <filesystem>

int z = 0;
class MainWidget : public az::Widget
{
	std::string name;
	std::unique_ptr<az::Image> img;
public:
	MainWidget(const std::string& name)
		:name(name)
	{
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


class MFrameBuffer : public az::Widget
{
	std::string name;
	GLuint fbo;
	GLuint framebufferTexture;
	az::Renderer renderer;
public:
	MFrameBuffer(const std::string& name)
		:name(name)
	{

	}

	void OnRender() override
	{
		ImGui::Begin(name.c_str());
		//FrameBuffer buffer;
		//buffer.Bind();
		//ImGui::Image((void*)buffer.GetColorAttachmentRendererID(), {800.f,800.f});

		//ImVec2 pos = ImGui::GetCursorScreenPos();
		auto windowsize = ImGui::GetWindowSize();

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		az::Texture texture;

		//texture.Bind(1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo, 0);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, framebufferTexture, 0);

		float imageData[] =
		{//		x		y
			 -0.5f,	-0.5f,	// point 1
			  0.5f,	-0.5f,	// point 2
			  0.5f,	 0.5f,	// point 3
			 -0.5f,	 0.5f,	// point 4
		};

		unsigned int imageIndex[] =
		{
			0, 1, 2,		// triangle 1
			2, 3, 0,		// triangle 2
		};
		
		az::VertexArray va;
		az::VertexBuffer vb(imageData, 4 * 2 * sizeof(float));
		va.Bind();
		vb.Bind();
		az::VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		az::Shader shader("D:/Files/myshader2.shader");
		shader.Bind();

		az::IndexBuffer ib(imageIndex, 6);
		//glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		//renderer.Clear();
		renderer.Draw(va, ib, shader);

		ImGui::Image((void*)fbo, ImVec2(ImGui::GetWindowSize().x - 40, ImGui::GetWindowSize().y - 40));
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		va.Unbind();
		vb.Unbind();
		shader.Unbind();

		ImGui::End();
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
	Application::WindowStyle style;
	style.width = 800;
	style.height = 400;
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