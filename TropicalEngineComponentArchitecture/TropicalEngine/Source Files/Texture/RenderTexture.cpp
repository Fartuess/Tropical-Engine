#include <Utills/Exception.h>

#include <Texture/RenderTexture.h>
#include <Texture/TextureManager.h>

namespace TropicalEngine
{

	RenderTexture::RenderTexture(QString name, int width, int height) : Texture(name)
	{
		this->width = width;
		this->height = height;

		Create(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	}

	RenderTexture::~RenderTexture()
	{
		if (framebufferLocation != 0)
		{
			glDeleteFramebuffers(1, &framebufferLocation);
		}
	}

	void RenderTexture::BindFramebuffer()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferLocation);
		glViewport(0, 0, width, height);
	}

	void RenderTexture::BindDefaultFramebuffer()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void RenderTexture::Create(int wrappingS, int wrappingT)
	{
		glGenFramebuffers(1, &framebufferLocation);

		glGenTextures(1, &textureLocation);
		glBindTexture(GL_TEXTURE_2D, textureLocation);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingT);
		
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferLocation);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureLocation, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		
		GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
		
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			throw Exception<RenderTexture>("Framebuffer error: " + QString::number(status), this);
		}
	}

}