#pragma once

#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class made of set of different shaders for different shader passes.
	  */
	#pragma endregion
	class ShaderTechnique : public ISerializableJSON
	{
	public:
		TYPENAME(ShaderTechnique)

		#pragma region documentation
		/**
		  * \brief ShaderTechnique constructor.
		  *
		  * @param name Name for new ShaderTechnique.
		  * @param shaderBuilder ShaderBuilder to use for creation of this ShaderTechnique.
		  * @param isManaged Defines is this ShaderTechnique should be managed by ShaderManager.
		  */
		#pragma endregion
		ShaderTechnique(QString name, class AbstractShaderBuilder* shaderBuilder, bool managed = true);
		#pragma region documentation
		/**
		  * \brief ShaderTechnique constructor for creating ShaderTechnique made of only one Shader.
		  *
		  * @param name Name for new ShaderTechnique.
		  * @param shader Only Shader used by this ShaderTechnique.
		  * @param shaderPass Name of shader pass to use the only Shader with.
		  * @param isManaged Defines is this ShaderTechnique should be managed by ShaderManager.
		  */
		#pragma endregion
		ShaderTechnique(QString name, class Shader* shader, QString shaderPass = "Default", bool managed = true);
		#pragma region documentation
		/**
		  * \brief ShaderTechnique destructor.
		  */
		#pragma endregion
		~ShaderTechnique();

		#pragma region documentation
		/**
		  * \brief Gets the name of this ShaderTechnique.
		  *
		  * @return Name of this ShaderTechnique.
		  */
		#pragma endregion
		QString getName()	{ return name; };
		#pragma region documentation
		/**
		  * \brief Sets the name for this ShaderTechnique.
		  *
		  * @param name Name for this ShaderTechnique.
		  */
		#pragma endregion
		void setName(QString name)	{ this->name = name; };
		#pragma region documentation
		/**
		  * \brief Sets input for ShaderBuilder used for creating this ShaderTechnique.
		  *
		  * @param name Name of input parameter to set.
		  * @param path Path to file as input for selevted shader module.
		  */
		#pragma endregion
		void setInput(QString name, QString path);

		#pragma region documentation
		/**
		  * \brief Gets one of the Shaders making up this ShaderTechnique.
		  *
		  * If ShaderTechnique doesn't have Shader using selected shader pass, method will try to generate it using ShaderBuilder and set of inputs.
		  * @param shaderPass Shader pass to look for.
		  * @return Shader from this ShaderTechnique using selected shader pass.
		  */
		#pragma endregion
		class Shader* getShader(QString shaderPass = "Default");

		#pragma region documentation
		/**
		  * \brief Generates Shader for one of shader passes used by this ShaderTechnique.
		  *
		  * @param shaderPass Shader pass to generate Shader for.
		  * @return Generated Shader.
		  */
		#pragma endregion
		class Shader* generateShader(QString shaderPass = "Default");
		#pragma region documentation
		/**
		  * \brief Gets all shader passes and Shaders linked to them used in this ShaderTechnique.
		  *
		  * @return Collection of shader pass names and Shaders. Keys are names and values are Shaders.
		  */
		#pragma endregion
		QMap<QString, class Shader*> getShaderPasses()	{ return this->shaderPasses; }

		#pragma region documentation
		/**
		  * \brief Serializes ShaderTechnique to JSON.
		  *
		  * @return Serialized ShaderTechnique.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes JSON to ShaderTechnique.
		  *
		  * @return ShaderTechnique in form of IDeserializableFromJSON. Can be casted to ShaderTechnique directly.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

		static ShaderTechnique& InitializeType();

	protected:
		#pragma region documentation
		/**
		  * \brief Name of this ShaderTechnique.
		  */
		#pragma endregion
		QString name;
		#pragma region documentation
		/**
		  * \brief Says if this ShaderTechnique is managed by ShaderManager.
		  */
		#pragma endregion
		bool isManaged;
		#pragma region documentation
		/**
		  * \brief ShaderBuilder used to generate Shaders for this ShaderTechnique.
		  */
		#pragma endregion
		class AbstractShaderBuilder* shaderBuilder;
		#pragma region documentation
		/**
		  * \brief Collection of shader pass names and Shaders making up this ShaderTechnique. Keys are names and values are Shaders.
		  */
		#pragma endregion
		QMap<QString, class Shader*> shaderPasses;

		ShaderTechnique() {};

		#pragma region documentation
		/**
		  * \brief Collection of inputs for ShaderBuilder used by this ShaderTechnique. Keys are names of inputs and values are paths to shader module files.
		  */
		#pragma endregion
		QMap<QString, QString> inputs;
		
		static bool isTypeInitialized;
	};

}