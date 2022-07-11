#include "Texture.h"
#include "Logging/Log.h"
namespace az 
{
	Texture::Texture(uint32_t width, uint32_t height, const ImageFormat& format)
		:m_RendererID(0), m_Height(height), m_Width(width), m_BPP(0),m_format(format)
	{
		//if(CreateTextureInConstructor())
		CreateTexture();
	}
	Texture::Texture(unsigned char* buffer, uint32_t width, uint32_t height)
		: m_RendererID(0), m_Height(height), m_Width(width), m_BPP(0)
	{
		CreateTexture();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	}
	Texture::~Texture()
	{
		this->DeleteTexture();//THIS WILL DELETE THE TEXTURE BEFORE SHOWING IT IF ITS DEFINED IN OnUIRender()!
	}

	void Texture::CreateTexture()
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	void Texture::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_format == ImageFormat::RGBA ? 4 : 3;
		//ASSERT(size == m_Width * m_Height * bpp, "Data must be an entire texture!");
		if (size != m_Width * m_Height * bpp)
		{
			APPAZOID_ERROR("Data must be an entire texture!");
			throw "Data must be an entire texture!";
		}

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, ImageFormatToOpenGL(m_format), GL_UNSIGNED_BYTE, data);
	}
}