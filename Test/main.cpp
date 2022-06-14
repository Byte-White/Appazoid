// Appazoid.cpp : Defines the entry point for the application.
//
#include "Appazoid/Appazoid.h"

//#include <filesystem>

class TestLayer: public az::Layer
{
	unsigned int fbo;
	unsigned int texture;
public:
	TestLayer()
	{
	}

	void SetupFrameBuffer()
	{
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo, 0);
	}

	void OnConstruction() override
	{
		//SetupFrameBuffer();
		/*glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0,
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
		);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
	}
	
	void OnEvent(az::Event& e) override
	{
		az::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<az::KeyReleasedEvent>(AZ_BIND_EVENT_FN(TestLayer::OnKeyReleased));
	}

	bool OnKeyReleased(az::KeyReleasedEvent& e)
	{
		if (e.GetKeyCode() == az::Key::A) APPAZOID_INFO("\'A\' Got Released");
		return false;
	}

	void OnUIRender() override
	{
		static bool show_info = true;
		//static az::Ref<az::Image> viewport = az::make_ref<az::Image>("D:/Files/MG/img/2.png");
		//static az::Ref<az::Texture> texture = az::make_ref<az::Texture>();


		ImGui::Begin("Viewport");
		/*glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//here
		//static az::Texture data;
		static az::Renderer renderer;

		static float imageData[] =
		{//		x		y
			 -0.5f,	-0.5f,	// point 1
			  0.5f,	-0.5f,	// point 2
			  0.5f,	 0.5f,	// point 3
			 -0.5f,	 0.5f,	// point 4
		};

		static unsigned int imageIndex[] =
		{
			0, 1, 2,		// triangle 1
			2, 3, 0,		// triangle 2
		};

		az::VertexArray va;
		az::VertexBuffer vb(imageData, sizeof(imageData));
		va.Bind();
		vb.Bind();
		az::VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		az::IndexBuffer ib(imageIndex, 6);
		ib.Bind();

		az::Shader shader("D:/Files/myshader2.shader");
		shader.Bind();

		//glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		//renderer.Clear();
		//shader.SetUniform4f("u_Color", r, g, b, 1.0f);

		renderer.Draw(va, ib, shader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		ImGui::Image((void*)fbo, { ImGui::GetWindowSize().x - 50, ImGui::GetWindowSize().y - 50 });
		//here*/
		ImGui::End();

		ImGui::Begin("Status");
		ImGui::Checkbox("show info", &show_info);
		ImGui::SameLine();
		static bool show_col_editor = false;
		ImGui::Checkbox("show color editor", &show_col_editor);
		if(show_info)
		{
			ImGui::Text("Delta Time: %f", ImGui::GetIO().DeltaTime);
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "Framerate: %.2f", ImGui::GetIO().Framerate);
		}

		if(show_col_editor)
		{
			ImGui::Begin("Color Editor");
			az::app->window_style.ColorEditor();
			ImGui::End();
		}
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
	style.stylecolor = az::StyleColor::StyleColorDark;
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
	app->AddLayer<TestLayer>("test_layer");
	az::AppazoidSpecification::Print();
	az::MemoryTracker::Print();
	return app;
}