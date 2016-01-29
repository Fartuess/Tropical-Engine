#pragma once
#include <gtc/quaternion.hpp>

#include <QtCore/qlist.h>
#include <QtCore/qstring.h>

#include <Serialization/ISerializableJSON.h>

#include "TransformComponent.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Basic scene object with transform node. Functionality is extended by attaching components.
	  */
	#pragma endregion
	class Entity : public ISerializableJSON
	{
	private:
		QList<Component*> components;	//Had to be on top to initialize before transform component.

	public:
		TYPENAME(Entity)

		friend class Component;
		friend class Level;
		friend class PropertiesWidget;

		#pragma region documentation
		/**
		  * \brief Component describing position, rotation and scale of this Entity.
		  */
		#pragma endregion
		TransformComponent transform;
		#pragma region documentation
		/**
		  * \brief Name of the Entity.
		  */
		#pragma endregion
		QString name;

		#pragma region documentation
		/**
		  * \brief Constructor of Entity.
		  *
		  * @param position Position of Entity relative to parent.
		  * @param rotation Rotation of Entity relative to parent.
		  * @param scale Scale of Entity relative to parent.
		  */
		#pragma endregion
		Entity(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3 scale = glm::vec3(1.0f));
		#pragma region documentation
		/**
		  * \brief Constructor of Entity.
		  *
		  * @param transform Transform information for this Entity.
		  */
		#pragma endregion
		Entity(TransformComponent transform);
		#pragma region documentation
		/**
		  * \brief Destructor of Entity.
		  */
		#pragma endregion
		~Entity(void);

		#pragma region documentation
		/**
		  * \brief Gets parent Entity.
		  *
		  * @return Parent Entity.
		  */
		#pragma endregion
		Entity* getParrent();
		#pragma region documentation
		/**
		  * \brief Attaches other Entity to this one.
		  *
		  * @param subobject Other Entity.
		  */
		#pragma endregion
		void AttachSubobject(Entity* subobject);
		#pragma region documentation
		/**
		  * \brief Attaches this Entity to the other one.
		  *
		  * @param parrent Other Entity.
		  */
		#pragma endregion
		void AttachTo(Entity* parrent);
		#pragma region documentation
		/**
		  * \brief Attaches other Entity to this one.
		  *
		  * @param child Other Entity.
		  */
		#pragma endregion
		Entity& operator<<(Entity* child);
		#pragma region documentation
		/**
		  * \brief Gets list of child Entities.
		  *
		  * @return List of child Entities.
		  */
		#pragma endregion
		const QList<Entity*>& getSubobjects();

		#pragma region documentation
		/**
		  * \brief Attaches Component to this Entity.
		  *
		  * @param component Component to attach.
		  */
		#pragma endregion
		void AttachComponent(Component* component);
		#pragma region documentation
		/**
		  * \brief Detaches and deletes Component.
		  *
		  * @param component Component to delete.
		  */
		#pragma endregion
		void DeleteComponent(Component* component);	//is needed?
		#pragma region documentation
		/**
		  * \brief Attaches Component to this Entity.
		  *
		  * @param component Component to attach.
		  */
		#pragma endregion
		Entity& operator<<(Component* component);

		#pragma region documentation
		/**
		  * \brief Gets Level owning this Entity.
		  *
		  * @return Level owning this Entity.
		  */
		#pragma endregion
		class Level* getLevel()	{ return level; }

		#pragma region documentation
		/**
		  * \brief Serializes Entity to JSON.
		  *
		  * @return Serialized Entity.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes JSON to Entity.
		  *
		  * @return Entity in form of IDeserializableFromJSON. Can be casted to Entity directly.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	private:
		Entity* parrent = nullptr;
		class Level* level = nullptr;
		QList<Entity*> subobjects;

		void DetachComponent(Component* component);

		void setLevel(class Level* level);
	};

}