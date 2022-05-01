#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#pragma once
#include "glad/glad.h"

#include <csignal>
#include <string>

using std::string;


namespace az
{

	#define ASSERT(x) if (!(x)) __debugbreak()//raise(SIGABRT);  // __debugbreak()
	#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))



	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
	class Renderer {
	public:
		void Clear() const;
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}