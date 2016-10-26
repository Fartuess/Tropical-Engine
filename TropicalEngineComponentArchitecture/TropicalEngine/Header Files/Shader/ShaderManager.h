#pragma once
#include <GL/glew.h>

#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include <Utills/Singleton.h>

#include "Shader.h"

namespace TropicalEngine
{

	// TODO: Finish documenting it.
	#pragma region documentation
	/**
	  * \brief Class for managing Shaders.
	  */
	#pragma endregion
	class ShaderManager : public Singleton<ShaderManager>
	{
	public:

		friend class Shader;

		struct shaderProgram
		{
			GLuint program;

			GLuint computeShader;
			GLuint vertexShader;
			GLuint controlTessalationShader;
			GLuint evaluationTessalationShader;
			GLuint geometryShader;
			GLuint fragmentShader;
		};

		#pragma region documentation
		/**
		  * \brief ShaderManager constructor.
		  */
		#pragma endregion
		ShaderManager(void);
		#pragma region documentation
		/**
		  * \brief ShaderManager destructor.
		  */
		#pragma endregion
		~ShaderManager(void);

		#pragma region documentation
		/**
		  * \brief Gets Shader which is currently used for drawing.
		  *
		  * @return Shader which is currently used for drawing.
		  */
		#pragma endregion
		Shader* const getCurrentShader();
		#pragma region documentation
		/**
		  * \brief Sets Shader which will be now used for drawing.
		  *
		  * @param shader Shader which will be now used for drawing. 
		  */
		#pragma endregion
		void setCurrentShader(Shader* shader);

		#pragma region documentation
		/**
		  * \brief Checks if there is Shader with given name.
		  *
		  * @param name Name of Shader to check for.
		  *
		  * @return Information if there is Shader with given name.
		  */
		#pragma endregion
		bool containsShader(QString name);

		#pragma region documentation
		/**
		  * \brief Checks if there is ShaderTechnique with given name.
		  *
		  * @param name Name of ShaderTechnique to check for.
		  *
		  * @return Information if there is ShaderTechnique with given name.
		  */
		#pragma endregion
		bool containsShaderTechnique(QString name);

		#pragma region documentation
		/**
		  * \brief Gets Shader with given name.
		  *
		  * @param name Name of Shader to look for.
		  * @return Shader with given name.
		  */
		#pragma endregion
		Shader* const getShader(QString name);
		#pragma region documentation
		/**
		  * \brief Gets ShaderTechnique with given name.
		  *
		  * @param name Name of ShaderTechnique to look for.
		  * @return ShaderTechnique with given name.
		  */
		#pragma endregion
		class ShaderTechnique* getShaderTechnique(QString name);

		#pragma region documentation
		/**
		  * \brief Gets Shader with given name.
		  *
		  * @param name Name of Shader to look for.
		  * @return Shader with given name.
		  */
		#pragma endregion
		Shader* operator[](QString name) { return shaders[name]; }
		#pragma region documentation
		/**
		  * \brief Gets Shader with given name.
		  *
		  * @param name Name of Shader to look for.
		  * @return Shader with given name.
		  */
		#pragma endregion
		const Shader* operator[](QString name) const { return shaders[name]; }

		#pragma region documentation
		/**
		  * \brief Creates and loads Shader created from suplied vertex and fragment shader.
		  *
		  * @param name Name for new Shader.
		  * @param vertexShader Path to vertex shader file.
		  * @param fragmentShader Path to fragment shader file.
		  * @return Created Shader.
		  */
		#pragma endregion
		Shader* Load(QString name, QString vertexShader, QString fragmentShader);
		#pragma region documentation
		/**
		  * \brief Loads existing Shader.
		  *
		  * @param shader Shader to load.
		  * @param name Alias of Shader kept in manager.
		  */
		#pragma endregion
		void Load(Shader* shader, QString name);
		#pragma region documentation
		/**
		  * \brief Loads existing ShaderTechnique.
		  *
		  * @param shaderTechnique to load.
		  * @param name Alias of ShaderTechnique kept in manager.
		  */
		#pragma endregion
		void Load(class ShaderTechnique* shaderTechnique, QString name);

		#pragma region documentation
		/**
		  * \brief Sets different Shader to use in next drawing.
		  *
		  * @param name Name of Shader to use for next drawing.
		  */
		#pragma endregion
		void UseShader(QString name);
		#pragma region documentation
		/**
		  * \brief Sets different Shader to use in next drawing.
		  *
		  * @param shader Shader to use for next drawing.
		  */
		#pragma endregion
		void UseShader(Shader* shader);

		#pragma region documentation
		/**
		  * \brief Gets Shader Builder with a given name.
		  *
		  * @param name Name of Shader Builder to get.
		  *
		  * @return Shader Builder with given name.
		  */
		#pragma endregion
		class AbstractShaderBuilder* getShaderBuilder(QString name) { return shaderBuilders[name]; }
		#pragma region documentation
		/**
		  * \brief Registers Shader Builder to the ShaderManager.
		  *
		  * @param name Alias for Shader Builder.
		  * @param shaderBuilder Shader Builder to register.
		  */
		#pragma endregion
		void registerShaderBuilder(QString name, class AbstractShaderBuilder* shaderBuilder);

	protected:
		QHash<QString, class ShaderTechnique*> shaderTechniques;
		QHash<QString, Shader*> shaders;
		Shader* currentShader;	//shader currently enabled on GPU

		QHash<QString, class AbstractShaderBuilder*> shaderBuilders;

		void FlushShader(QString name);
	};

}