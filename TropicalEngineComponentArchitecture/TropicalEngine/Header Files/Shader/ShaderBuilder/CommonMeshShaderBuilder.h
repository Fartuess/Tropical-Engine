#pragma once
#include <QtCore/QString>

#include <Utills/Singleton.h>

#include "AbstractShaderBuilder.h"

namespace TropicalEngine
{

	// TODO: Write detailed class description.
	#pragma region documentation
	/**
	  * \brief Class generating Shaders.
	  *
	  * Stub for later detailed description.
	  */
	#pragma endregion
	class CommonMeshShaderBuilder : public AbstractShaderBuilder, public Singleton<CommonMeshShaderBuilder>
	{
	public:
		#pragma region documentation
		/**
		  * \brief CommonMeshShaderBuilder constructor.
		  */
		#pragma endregion
		CommonMeshShaderBuilder();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~CommonMeshShaderBuilder();

		#pragma region documentation
		/**
		  * \brief Resets values of all input parameters to default ones.
		  */
		#pragma endregion
		virtual void resetInputs() override;

		#pragma region documentation
		/**
		  * \brief Generates Shader from modules described by current inputs.
		  *
		  * @param shaderName Name for created Shader.
		  * @param shaderPass Name of shader pass new shader will be using.
		  * @return Created Shader.
		  */
		#pragma endregion
		virtual class Shader* createShader(QString shaderName, QString shaderPass = "Default") override;
	protected:
		#pragma region documentation
		/**
		  * \brief File Path to constant lighting shader module.
		  */
		#pragma endregion
		QString lighting;
		#pragma region documentation
		/**
		  * \brief File Path to constant core shader module.
		  */
		#pragma endregion
		QString shaderCore;
	};

}