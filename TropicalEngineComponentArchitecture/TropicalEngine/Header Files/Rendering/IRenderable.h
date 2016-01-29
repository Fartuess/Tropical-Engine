#pragma once

#include <QtCore/qset.h>
#include <QtCore/qstring.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Interface for renderable objects.
	  */
	#pragma endregion
	class IRenderable
	{
	public:
		#pragma region documentation
		/**
		  * \brief Gets set of names of used shaderpasses.
		  *
		  * @return Set of names of used shaderpasses.
		  */
		#pragma endregion
		virtual QSet<QString> getShaderPasses() = 0;
		#pragma region documentation
		/**
		  * \brief Tells if this object is using shader pass with given name.
		  *
		  * @param shaderPass Name of shader pass.
		  * @return bool value telling if this object is using shader pass with given name.
		  */
		#pragma endregion
		virtual bool hasShaderPass(QString shaderPass);
		#pragma region documentation
		/**
		  * \brief Draws object.
		  *
		  * @param camera Camera to render from.
		  * @param shaderPass Name of shader pass to render with.
		  */
		#pragma endregion
		virtual void Draw(class CameraComponent* camera, QString shaderPass = "Default") = 0;
	};

}