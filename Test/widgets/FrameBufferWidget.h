#pragma once
class MFrameBuffer : public az::Widget
{
	std::string name;
	GLuint framebufferTexture;
	az::Renderer renderer;
	az::Texture* texture;
public:
	MFrameBuffer(const std::string& name)
		:name(name)
	{

	}

	void OnConstruction() override
	{
	}

	void OnRender() override
	{
		ImGui::Begin(name.c_str());
		//FrameBuffer buffer;
		//buffer.Bind();
		//ImGui::Image((void*)buffer.GetColorAttachmentRendererID(), {800.f,800.f});

		//ImVec2 pos = ImGui::GetCursorScreenPos();

		GLuint fbo;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		texture = new az::Texture();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		//texture.Bind(1);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			APPAZOID_INFO("ITS COMPLETED!!!!");
		else APPAZOID_WARN("BAD NEWS...");

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
		///va.Bind();
		///vb.Bind();
		az::VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		az::IndexBuffer ib(imageIndex, 6);

		az::Shader shader("D:/Files/myshader2.shader");
		shader.Bind();

		//glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		//renderer.Clear();

		shader.Bind();
		//shader.SetUniform4f("u_Color", r, g, b, 1.0f);

		va.Bind();
		ib.Bind();

		renderer.Draw(va, ib, shader);

		ImGui::Image((void*)texture->GetTextureID(), ImVec2(ImGui::GetWindowSize().x - 40, ImGui::GetWindowSize().y - 40));
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		shader.Unbind();

		ImGui::End();
	}
	void OnImGuiRender() override
	{
		delete texture;
	}
private:

};
