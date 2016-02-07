#pragma once
#include <glm.hpp>

#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtCore/qhash.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for building and importing Model assets.
	  */
	#pragma endregion
	class ModelBuilder : public Singleton<ModelBuilder>
	{
	public:
		friend class ModelManager;

		#pragma region documentation
		/**
		  * \brief Constructor for ModelBuilder class.
		  */
		#pragma endregion
		ModelBuilder(void);
		#pragma region documentation
		/**
		  * \brief Destructor for ModelBuilder class.
		  */
		#pragma endregion
		~ModelBuilder(void);

		#pragma region documentation
		/**
		  * \brief Loads model.
		  *
		  * Loads and adds model to ModelManager.
		  *
		  * @param name Name of the model to be set.
		  * @param fileUrl path to model file.
		  * @return Loaded Model.
		  */
		#pragma endregion
		class Model* Load(QString name, QString fileUrl);

		void CalculateTangentsBitangents(QVector<glm::vec4>& vertices, QVector<glm::vec3>& normals, QVector<glm::vec2>& texcoords, QVector<glm::vec3>& out_tangents, QVector<glm::vec3>& out_bitangents);

		#pragma region documentation
		/**
		  * \brief Gets ModelBuilder with asked name.
		  *
		  * @param name Name of ModelBuilder to get.
		  * @return ModelBuilder with asked name.
		  */
		#pragma endregion
		class AbstractModelBuilder* getModelBuilder(QString name);

		// TODO: Figure out if it should be static?
		#pragma region documentation
		/**
		  * \brief Adds new ModelBuilder to the library.
		  * 
		  * @param modelBuilder ModelBuilder to add.
		  */
		#pragma endregion
		void AddModelBuilder(class AbstractModelBuilder* modelBuilder);
		#pragma region documentation
		/**
		  * \brief Adds support of specific importer for ModelBuilder.
		  *
		  * @param importer Importer to support.
		  */
		#pragma endregion
		static void AddImporter(class AbstractModelImporter* importer);

	private:
		static QHash<QString, class AbstractModelImporter*> supportedExtensions;
		static QHash<QString, class AbstractModelBuilder*> supportedShapes;

		class Model* Load(QString fileUrl);
	};

}