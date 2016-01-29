#pragma once
#include "Texture.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief RenderTexture is a Texture GPU can render to.
	  */
	#pragma endregion
	class RenderTexture : public Texture
	{
	public:
		TYPENAME(RenderTexture)

		#pragma region documentation
		/**
		* \brief RenderTexture constructor.
		*
		* @param name Name for new RenderTexture.
		* @param width Width for new RenderTexture.
		* @param height Height for new RenderTexture
		*/
		#pragma endregion
		RenderTexture(QString name, int width, int height);
		#pragma region documentation
		/**
		* \brief RenderTexture destructor.
		*/
		#pragma endregion
		~RenderTexture();

		#pragma region documentation
		/**
		* \brief Binds this RenderTexture for use.
		*/
		#pragma endregion
		void BindFramebuffer();
		#pragma region documentation
		/**
		* \brief Binds default rendering target.
		*/
		#pragma endregion
		static void BindDefaultFramebuffer();
	protected:
		#pragma region documentation
		/**
		* \brief Width of RenderTexture.
		*/
		#pragma endregion
		int width;
		#pragma region documentation
		/**
		* \brief Height of RenderTexture.
		*/
		#pragma endregion
		int height;

		#pragma region documentation
		/**
		  * \brief Initialization of RenderTexture.
		  */
		#pragma endregion
		virtual void Create() override;
	private:
		GLuint framebufferLocation;
	};

}