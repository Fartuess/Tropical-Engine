#pragma once
#include <QtCore/qstring.h>

#include <Serialization/ISerializableJSON.h>

#include "Entity.h"
#include "TransformComponent.h"

namespace TropicalEngine
{
	
	#pragma region documentation
	/**
	  * \brief Level class.
	  */
	#pragma endregion
	class Level : public ISerializableJSON
	{
	public:
		TYPENAME(Level)

		#pragma region documentation
		/**
		  * \brief Level name.
		  */
		#pragma endregion
		QString name;

		#pragma region documentation
		/**
		  * \brief Level constructor.
		  *
		  * @param name Name of Level.
		  * @param position Position of the root Entity of the level.
		  * @param rotation Rotation of the root Entity of the level.
		  * @param scale Scale of the root Entity of the level.
		  */
		#pragma endregion
		Level(QString name, glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(), glm::vec3 scale = glm::vec3(1.0f));
		#pragma region documentation
		/**
		  * \brief Level constructor.
		  *
		  * @param transform Transformation for root Entity of the level.
		  * @param name Name for the level.
		  */
		#pragma endregion
		Level(TransformComponent transform, QString name = "");
		#pragma region documentation
		/**
		  * \brief Level destructor.
		  */
		#pragma endregion
		~Level(void);

		#pragma region documentation
		/**
		  * \brief Gets root Entity of the Level.
		  *
		  * @return Root Entity of the Level.
		  */
		#pragma endregion
		Entity* const getRoot();
		#pragma region documentation
		/**
		  * \brief Gets internal Package of this Level.
		  *
		  * @return Internal Package of this Level.
		  */
		#pragma endregion
		class Package* const getInternalPackage();

		#pragma region documentation
		/**
		  * \brief Attaches Entity to this level.
		  *
		  * @param object Entity to add.
		  */
		#pragma endregion
		void AttachObject(Entity* object);
		#pragma region documentation
		/**
		  * \brief Attaches Entity to this level.
		  *
		  * @param object Entity to add.
		  */
		#pragma endregion
		Level& operator<<(Entity* object);

		#pragma region documentation
		/**
		  * \brief Serializes Level to JSON.
		  *
		  * @return Serialized Level.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes JSON to Level.
		  *
		  * @return Level in form of IDeserializableFromJSON. Can be casted to Level directly.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	private:
		Entity* root;

		class Package* internalPackage;
		QHash<QString, class Package*> usedPackages;
	};

}