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
		ImGui::Text("Framerate: %.2f", ImGui::GetIO().Framerate);
		ImGui::End();
	}
private:

};


class ContentBrowser : public az::Widget
{
	std::string m_folder_path;
	az::Texture* t;
public:
	ContentBrowser(const std::string& folder_path)
		:m_folder_path(folder_path)
	{
	}
	~ContentBrowser()
	{
		delete t;
	}

	void OnRender() override
	{
		ImGui::Begin(m_folder_path.c_str());
		//for()
		ImGui::Button("TODO: make a content browser.");
		t = new az::Texture("D:/Files/logo.jpg");

		static int sz[2] = {t->GetWidth(),t->GetHeight()};
		ImGui::SliderInt2("size:",sz,24,1024);
		t->Bind();
		ImGui::Image((void*)(t->GetTextureID()), {(float)sz[0],(float)sz[1]});
		t->Unbind();
		ImGui::End();
	}
private:

};


class MFrameBuffer : public az::Widget
{
	std::string name;
	GLuint fbo;
	GLuint texture;
	GLuint depth_texture;
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

		
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		glGenTextures(1, &depth_texture);
		glBindTexture(GL_TEXTURE_2D, depth_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

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

		az::Renderer renderer;
		renderer.Draw(va, ib, shader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		drawList->AddImage((void*)fbo,
			pos,
			ImVec2(pos.x + ImGui::GetWindowSize().x, pos.y + ImGui::GetWindowSize().x),
			ImVec2(0, 1),
			ImVec2(1, 0));
		

		ImGui::End();
	}
private:

};

void ConfigFlags(ImGuiIO& io)
{
	az::EnableConfigFlag(io,ImGuiConfigFlags_DockingEnable);
	az::EnableConfigFlag(io,ImGuiConfigFlags_NavEnableKeyboard);
	//az::EnableConfigFlag(io,ImGuiConfigFlags_ViewportsEnable);
}


az::Application* az::CreateApplication(int argc,char**argv)
{
	Application::WindowStyle style;
	style.width  = 800;
	style.height = 400;
	style.title  = "Appazoid Application";
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
	//app->AddWidget<MFrameBuffer>("framebuffer_widget", "FrameBuffer");//TODO: Fix the errors
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