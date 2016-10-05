#include <Utills/Exception.h>

#include <Texture/RenderTexture.h>
#include <Texture/TextureManager.h>

namespace TropicalEngine
{

	RenderTexture::RenderTexture(QString name, int width, int height, RenderTexture::targetType type) : Texture(name)
	{
		this->width = width;
		this->height = height;
		this->type = type;

		//Create(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		Create(GL_REPEAT, GL_REPEAT);

		TextureManager::instance().RegisterTexture(name, this);
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
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferLocation);
		glViewport(0, 0, width, height);
	}

	void RenderTexture::BindDefaultFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderTexture::Create(int wrappingS, int wrappingT)
	{
		glGenFramebuffers(1, &framebufferLocation);
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferLocation);

		glGenTextures(1, &textureLocation);
		glBindTexture(GL_TEXTURE_2D, textureLocation);
		
		if (type == targetType::Color)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingT);

			// TODO: Figure out if necessary
			//temp{

			GLuint depthLocation;

			glGenTextures(1, &depthLocation);
			glBindTexture(GL_TEXTURE_2D, depthLocation);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingT);

			//}temp

			//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureLocation, 0);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureLocation, 0);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthLocation, 0);

			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			glReadBuffer(GL_COLOR_ATTACHMENT0);
		}
		else if (type == targetType::Depth)
		{
			glGenTextures(1, &textureLocation);
			glBindTexture(GL_TEXTURE_2D, textureLocation);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingT);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureLocation, 0);

			glDrawBuffer(GL_DEPTH_ATTACHMENT);
			glReadBuffer(GL_DEPTH_ATTACHMENT);
		}
		
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			throw Exception<RenderTexture>("Framebuffer error: " + QString::number(status), this);
		}
	}

}