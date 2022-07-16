#pragma once

#pragma once

namespace az
{
	struct FrameBufferSpecification
	{
		unsigned int Width, Height;
		unsigned int Samples = 1;
		bool SwapChainTarget = false;
	};
	class Framebuffer
	{
	private:
		unsigned int m_Framebuffer, m_ColorAttachment, m_DepthAttachment;
		FrameBufferSpecification m_Specification;
	public:
		Framebuffer(const FrameBufferSpecification& spec);
		~Framebuffer();

		void Resize();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetColorAttachment() const	{ return m_ColorAttachment; }


	};
}