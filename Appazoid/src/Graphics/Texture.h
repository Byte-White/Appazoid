#pragma once
#pragma once
#include <string>
#include <glad/glad.h>
#include "stb_image.h"
#include "glm/glm.hpp"
namespace az
{
	class Texture
	{
	protected:
		GLuint m_RendererID;
		std::string m_FilePath;
		int m_Width, m_Height, m_BPP;
		//inline virtual bool CreateTextureInConstructor() { return true; }//override it to return false to disable the CreateTexture() in the constructor //not needed right now(used it for tests)
	public:
		Texture();
		Texture(unsigned char* buffer);
		virtual ~Texture();
		void CreateTexture();
		inline void DeleteTexture() { glDeleteTextures(1, &m_RendererID); }
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
		inline glm::vec2 GetSize() const { return glm::vec2{ (float)m_Width,(float)m_Height }; }

	protected:
	};
}
