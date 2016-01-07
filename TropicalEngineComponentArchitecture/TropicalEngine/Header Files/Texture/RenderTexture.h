#pragma once
#include "Texture.h"

namespace TropicalEngine
{

	class RenderTexture : public Texture
	{
	public:
		TYPENAME("RenderTexture")

			RenderTexture(QString name, int width, int height);
		~RenderTexture();

		void BindFramebuffer();
		static void BindDefaultFramebuffer();
	protected:
		int width;
		int height;

		virtual void Create() override;
	private:
		GLuint framebufferLocation;
	};

}