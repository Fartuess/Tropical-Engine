#pragma once
#include <QtCore/qmap.h>

namespace TropicalEngine
{
	#pragma region documentation
	/**
	  * \brief Base class for ShaderBuilders.
	  */
	#pragma endregion
	class AbstractShaderBuilder
	{
	public:
		friend class ShaderTechnique;

		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		AbstractShaderBuilder()	{}
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~AbstractShaderBuilder()	{}

		/// TODO: Maybe replace QString with QVariant?
		#pragma region documentation
		/**
		  * \brief Sets path to the input module.
		  *
		  * @param name Name of module socket to fill.
		  * @param path Path to shader file for selected module.
		  */
		#pragma endregion
		void setInput(QString name, QString path);
		#pragma region documentation
		/**
		  * \brief Resets values of all input parameters to default ones.
		  */
		#pragma endregion
		virtual void resetInputs() = 0;
		
		#pragma region documentation
		/**
		  * \brief Gets path to the input module.
		  *
		  * @param name Name of module socket to get.
		  * @return Path to shader file for selected module.
		  */
		#pragma endregion
		QString& operator[](QString name)      { return inputs[name]; };
		#pragma region documentation
		/**
		  * \brief Gets path to the input module.
		  *
		  * @param name Name of module socket to get.
		  * @return Path to shader file for selected module.
		  */
		#pragma endregion
		const QString operator[](QString name) const { return inputs[name]; };

		#pragma region documentation
		/**
		  * \brief Generates Shader from modules described by current inputs.
		  *
		  * @param shaderName Name for created Shader.
		  * @param shaderPass Name of shader pass new shader will be using.
		  * @return Created Shader.
		  */
		#pragma endregion
		virtual class Shader* createShader(QString shaderName, QString shaderPass = "Default") = 0;
	protected:
		/// TODO: Maybe replace QString with QVariant?
		#pragma region documentation
		/**
		  * \brief Inputs for the generator.
		  *
		  * Key is name of module and value is path to the shader file for that module.
		  */
		#pragma endregion
		QMap<QString, QString> inputs;
	};

}