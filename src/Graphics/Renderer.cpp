/*
 * Renderer.cpp
 *
 *  Created on: 13 de dez de 2017
 *      Author: Casa
 */
#include "Renderer.h"
#include <iostream>

namespace az
{
	void GLClearError() {
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall(const char* function, const char* file, int line) {
		while (GLenum error = glGetError()) 
		{
			//std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << " " << line << std::endl;//TODO: Add With SPDLOG
			APPAZOID_CORE_CRITICAL("[OpenGL Error] ({0}) {1} {2} {3}", error, function, file, line);
			return false;
		}
		return true;
	}



	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::Clear() const {
		//GLCall(glClear(GL_COLOR_BUFFER_BIT));
		#if AZ_RENDER_API == AZ_RENDER_API_OPENGL
		glClear(GL_COLOR_BUFFER_BIT);
		#elif AZ_RENDER_API == AZ_RENDER_API_VULKAN
		
		#endif

	}
}