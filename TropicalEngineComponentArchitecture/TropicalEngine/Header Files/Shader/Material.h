#pragma once
#include <glm.hpp>

#include <Serialization/ISerializableJSON.h>

#include "MaterialParameter.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief class for Material support.
	  *
	  * Material is 'instance of Shader or ShaderTechnique' with specific set of shader parameter values (uniforms).
	  */
	#pragma endregion
	class Material : public ISerializableJSON
	{
	public:
		TYPENAME(Material)

		#pragma region documentation
		/**
		  * \brief Gets name of the Material.
		  */
		#pragma endregion
		QString getName()	{ return name; }
		#pragma region documentation
		/**
		  * \brief Sets name of the Material.
		  */
		#pragma endregion
		void setName(QString name);

		#pragma region documentation
		/**
		  * \brief Material constructor.
		  *
		  * Creates Material using only one Shader.
		  * @param shader Shader to use.
		  * @param name Name for the Material.
		  */
		#pragma endregion
		Material(class Shader* shader, QString name);
		#pragma region documentation
		/**
		  * \brief Material constructor.
		  *
		  * Creates Material using Shader technique composed of multiple Shader for different shader passes.
		  * @param shaderTechnique ShaderTechnique to use.
		  * @param name Name for the Material.
		  */
		#pragma endregion
		Material(class ShaderTechnique* shaderTechnique, QString name);
		#pragma region documentation
		/**
		  * \brief Material destructor.
		  */
		#pragma endregion
		~Material(void);

		#pragma region documentation
		/**
		  * \brief Gets Shader used by this Material.
		  *
		  * @return Shader of nullptr if Material is using ShaderTechnique.
		  */
		#pragma endregion
		class Shader* getShader()	{ return shader; }
		#pragma region documentation
		/**
		  * \brief Gets ShaderTechnique used by this Material.
		  *
		  * @return ShaderTechnique or nullptr if Material is using single Shader.
		  */
		#pragma endregion
		class ShaderTechnique* getShaderTechnique()	{ return shaderTechnique; }

		#pragma region documentation
		/**
		  * \brief Method for use in renderable objects to set up drawing with this Material.
		  */
		#pragma endregion
		void Use();

		bool hasParameter(QString name);
		MaterialParameter* getParameter(QString name);

		#pragma region documentation
		/**
		  * \brief Sets value of material parameter.
		  *
		  * @param name Name of the parameter.
		  * @param parameter pointer to new value of the parameter.
		  */
		#pragma endregion
		void setParameter(QString name, void* parameter);

		#pragma region documentation
		/**
		  * \brief Gets material parameter.
		  *
		  * @param name Name of the parameter.
		  */
		#pragma endregion
		MaterialParameter& operator[](QString name) { return parameters[name]; };
		#pragma region documentation
		/**
		  * \brief Gets material parameter.
		  *
		  * @param name Name of the parameter.
		  */
		#pragma endregion
		const MaterialParameter operator[](QString name) const { return parameters[name]; };

		#pragma region documentation
		/**
		  * \brief Serializes Material to JSON.
		  *
		  * @return Serialized Material.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes JSON to Material.
		  *
		  * @return Material in form of IDeserializableFromJSON. Can be casted to Material directly.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		#pragma region documentation
		/**
		  * \brief Name of this Material.
		  */
		#pragma endregion
		QString name;
		#pragma region documentation
		/**
		  * \brief Shader used by this Material.
		  *
		  * Shader used by this Material. If Material uses ShaderTechnique this value is nullptr.
		  */
		#pragma endregion
		class Shader* shader;
		#pragma region documentation
		/**
		  * \brief ShaderTechnique used by this Material.
		  *
		  * ShaderTechnique used by this Material. If Material uses single Shader this value is nullptr.
		  */
		#pragma endregion
		class ShaderTechnique* shaderTechnique;
		#pragma region documentation
		/**
		  * \brief Collection of MaterialParameters of this Material.
		  *
		  * Collection of MaterialParameters of this Material. Key is name of parameter and value is value.
		  */
		#pragma endregion
		QMap<QString, MaterialParameter> parameters;

	private:
		void ActivateParameter(QString name, void* value);

		void ActivateParameter(GLuint location, bool* value);
		void ActivateParameter(GLuint location, float* value);
		void ActivateParameter(GLuint location, glm::vec2* value);
		void ActivateParameter(GLuint location, glm::vec3* value);
		void ActivateParameter(GLuint location, glm::vec4* value);
		void ActivateParameter(GLuint location, glm::mat3* value);
		void ActivateParameter(GLuint location, glm::mat4* value);
		void ActivateParameter(GLuint location, class Texture* value);
		void ActivateParameter(GLuint location, class CubemapTexture* value);
	};

}