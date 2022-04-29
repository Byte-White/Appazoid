#pragma once
#include <string>
#include <glad/glad.h>
#include "stb_image.h"
namespace az
{
	class Texture
	{
	private:
		GLuint m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	public:
		Texture(const std::string& path)
			:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Height(0), m_Width(0), m_BPP(0)
		{
			//stbi_set_flip_vertically_on_load(1);
			m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, nullptr, 4);

			if (m_LocalBuffer == NULL)
				std::abort();

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			// Upload pixels into texture
			#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			#endif

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
			//glBindTexture(GL_TEXTURE_2D, 0);
			//if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
		}
		~Texture()
		{
			//glDeleteTextures(1, &m_RendererID);//THIS WILL DELETE THE TEXTURE BEFORE SHOWING IT!
		}

		void Bind(unsigned int slot = 0) const
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);
		}
		void Unbind()const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		inline GLuint GetTextureID() const { return m_RendererID; }

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline ImVec2 GetSize() const { return {(float)m_Width,(float)m_Height}; }

	protected:
	};
}
