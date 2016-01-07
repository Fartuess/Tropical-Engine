#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

namespace TropicalEngine
{

	class Model;
	class ModelBuilder;

	/**
	  * Class for managing loaded Model asset data.
	  */
	class ModelManager
	{
	public:
		friend class ModelComponent;
		friend class ModelBuilder;

		/**
		  * \brief Constructor for ModelManger.
		  */
		ModelManager(void);

		/**
		  * \brief Destructor for ModelManger.
		  */
		~ModelManager(void);

		/**
		  * \brief Gets model asset by name.
		  *
		  * @param name Name to look for.
		  * @return Found Model.
		  */
		Model* getModel(QString name);

		/**
		  * \brief Gets model asset by name.
		  *
		  * @param name Name to look for.
		  * @return Found Model.
		  */
		Model* operator[](QString name)      { return models[name]; };

		/**
		  * \brief Gets model asset by name.
		  *
		  * @param name Name to look for.
		  * @return Found Model.
		  */
		const Model* operator[](QString name) const { return models[name]; };

		/**
		  * \brief Imports models from a file.
		  *
		  * Imports model from a file using proper model importer and then loads it into the manager.
		  * @param name Name of the model to be set after importing.
		  * @param fileUrl Path to the model file.
		  * @return Loaded Model.
		  */
		void Load(QString fileUrl, QString name);

		/**
		  * \brief Loads imported model to the manager.
		  *
		  * @param model Model to load to the manager.
		  * @param name Name of the model to be set after importing.
		  */
		void Load(Model* model, QString name);

	private:
		QHash<QString, Model*> models;

		void FlushModel(QString name, bool forced = false);
	};

}