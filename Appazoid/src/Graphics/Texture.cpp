#include "Texture.h"
#include "Logging/Log.h"
namespace az 
{
	Texture::Texture(const ImageFormat& format)
		:m_RendererID(0), m_Height(0), m_Width(0), m_BPP(0),m_format(format)
	{
		//if(CreateTextureInConstructor())
		CreateTexture();
	}
	Texture::Texture(unsigned char* buffer)
		: m_RendererID(0), m_Height(0), m_Width(0), m_BPP(0)
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

}