#pragma once
#include "Core/AppazoidSpecification.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#pragma once
#include "glad/glad.h"

#include <csignal>
#include <string>

#include "Core/PlatformDetection.h"
using std::string;


namespace az
{
	#ifdef AZ_PLATFORM_WINDOWS
	#define ASSERT(x) if (!(x)) __debugbreak()//raise(SIGABRT);  // __debugbreak()
	#else
	#define ASSERT(x) 
	#endif
	#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))
	

	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);
	class Renderer {
	public:
		static RenderAPI::API GetAPI() { return AppazoidSpecification::GetAPI(); }
		void Clear() const;
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		static void OnWindowResize(uint32_t width, uint32_t height)
		{
			glViewport(0, 0, width, height);
		}
	};
}