#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing loaded Model asset data.
	  */
	#pragma endregion
	class ModelManager : public Singleton<ModelManager>
	{
	public:
		friend class ModelComponent;
		friend class ModelBuilder;

		#pragma region documentation
		/**
		  * \brief Constructor for ModelManger.
		  */
		#pragma endregion
		ModelManager(void);
		#pragma region documentation
		/**
		  * \brief Destructor for ModelManger.
		  */
		#pragma endregion
		~ModelManager(void);

		#pragma region documentation
		/**
		  * \brief Gets model asset by name.
		  *
		  * @param name Name to look for.
		  * @return Found Model.
		  */
		#pragma endregion
		class Model* getModel(QString name);
		#pragma region documentation
		/**
		  * \brief Gets model asset by name.
		  *
		  * @param name Name to look for.
		  * @return Found Model.
		  */
		#pragma endregion
		class Model* operator[](QString name)	{ return models[name]; };
		#pragma region documentation
		/**
		  * \brief Gets model asset by name.
		  *
		  * @param name Name to look for.
		  * @return Found Model.
		  */
		#pragma endregion
		const class Model* operator[](QString name) const { return models[name]; };

		#pragma region documentation
		/**
		  * \brief Imports models from a file.
		  *
		  * Imports model from a file using proper model importer and then loads it into the manager.
		  * @param name Name of the model to be set after importing.
		  * @param fileUrl Path to the model file.
		  * @return Loaded Model.
		  */
		#pragma endregion
		void Load(QString fileUrl, QString name);
		#pragma region documentation
		/**
		  * \brief Loads imported model to the manager.
		  *
		  * @param model Model to load to the manager.
		  * @param name Name of the model to be set after importing.
		  */
		#pragma endregion
		void Load(class Model* model, QString name);

	private:
		QHash<QString, class Model*> models;

		void FlushModel(QString name, bool forced = false);
	};

}