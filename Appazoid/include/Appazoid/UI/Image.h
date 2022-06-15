#pragma once
#include <string>
#include <glad/glad.h>
#include "stb_image.h"
#include "Graphics/Texture.h"
namespace az
{
	class Image :public Texture
	{
	protected:
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
	public:
		Image(const std::string& path,ImageFormat format = ImageFormat::RGBA)
			:m_FilePath(path), m_LocalBuffer(nullptr), Texture(0,0,format)
		{
			//Texture's Constructor will get called.
			//stbi_set_flip_vertically_on_load(1);
			m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, nullptr, 4);

			if (m_LocalBuffer == NULL)
				std::abort();
			// Upload pixels into texture
			#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			#endif

			glTexImage2D(GL_TEXTURE_2D, 0, ImageFormatToOpenGL(m_format), m_Width, m_Height, 0, ImageFormatToOpenGL(m_format), GL_UNSIGNED_BYTE, m_LocalBuffer);
			//glBindTexture(GL_TEXTURE_2D, 0);
			if (m_LocalBuffer)
				stbi_image_free(m_LocalBuffer);

		}
		~Image()
		{
		}

	protected:
	};
}
