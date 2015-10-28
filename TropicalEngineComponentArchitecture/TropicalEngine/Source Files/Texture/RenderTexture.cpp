#include <Utills/Exception.h>

#include <Texture/RenderTexture.h>

RenderTexture::RenderTexture(QString name, int width, int height) : Texture(name)
{
	this->width = width;
	this->height = height;
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
}

void RenderTexture::BindDefaultFramebuffer()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void RenderTexture::Create()
{
	glGenFramebuffers(1, &framebufferLocation);

	glGenTextures(1, &textureLocation);
	glBindTexture(GL_TEXTURE_2D, textureLocation);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, framebufferLocation);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureLocation, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		throw Exception<RenderTexture>("Framebuffer error: " + QString::number(status), this);
	}
}