#pragma once
#include <QtCore/qstring.h>

#include <Serialization/ISerializableJSON.h>

#include <Package/Package.h>

#include "TransformComponent.h"
#include "Entity.h"

namespace TropicalEngine
{

	class Level : public ISerializableJSON
	{
	public:
		TYPENAME(Level)

		QString name;

		Level(QString name, glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(), glm::vec3 scale = glm::vec3(1.0f));
		Level(TransformComponent transform, QString name = nullptr);
		~Level(void);

		Entity* const getRoot();
		Package* const getInternalPackage();
		//Package* const getInternalPackage();	//do we need that?

		void AttachObject(Entity* object);
		Level& operator<<(Entity* object);

		QJsonObject toJSON() override;
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	private:
		Entity* root;

		Package* internalPackage;
		QHash<QString, Package*> usedPackages;
	};

}