#pragma once
#include "Appazoid/Appazoid.h"
class MFrameBuffer : public az::Layer
{
	std::string name;
	GLuint framebufferTexture;
	az::Texture* texture;
	GLuint fbo;
public:
	MFrameBuffer(const std::string& name)
		:name(name)
	{

	}

	void OnConstruction() override
	{
	}

	void OnUIRender() override
	{
        static az::Renderer renderer;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        texture = new az::Texture();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo, 0);

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
         az::VertexBuffer vb(imageData, sizeof(imageData));
        ///va.Bind();
        ///vb.Bind();
         az::VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        static az::IndexBuffer ib(imageIndex, 6);

        static az::Shader shader("D:/Files/myshader2.shader");
        shader.Bind();

        //glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        //renderer.Clear();

        shader.Bind();
        //shader.SetUniform4f("u_Color", r, g, b, 1.0f);

        va.Bind();
        ib.Bind();

        az::entrypoint::app->renderer.Draw(va, ib, shader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        ImGui::Begin("Windowwww");
        ImGui::Image((void*)fbo, { 800, 800 });
        ImGui::End();
	}
	void OnBufferSwap() override
	{
		//delete texture;
	}
private:

};
