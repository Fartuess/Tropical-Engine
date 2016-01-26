#include <Scene/Entity.h>

namespace TropicalEngine
{

	Entity::Entity(glm::vec3 position, glm::quat rotation, glm::vec3 scale) : transform(this, position, rotation, scale)
	{
		parrent = nullptr;
		///TODO: implement it.
	}

	Entity::Entity(TransformComponent transform) : transform(transform)
	{
		parrent = nullptr;
		///TODO: implement it.
	}

	Entity::~Entity(void)
	{
		//parrent = nullptr;
		///TODO: make sure it is properly implemented.
		QList<Entity*> helperSubobjectList = QList<Entity*>(subobjects);
		for (Entity* subobject : helperSubobjectList)
		{
			subobject->parrent = nullptr;
			delete subobject;
		}
		QList<Component*> helperComponentList = QList<Component*>(components);
		for (Component* component : helperComponentList)
		{
			if (component->getTypeName() != "Transform Component")	//transform component will remove by itself
			{
				delete component;
			}
		}
		if (parrent != nullptr)
		{
			parrent->subobjects.removeOne(this);
		}
	}

	Entity* Entity::getParrent()
	{
		return parrent;
	}

	void Entity::AttachSubobject(Entity* subobject)
	{
		if (subobject != nullptr)
		{
			subobjects.append(subobject);
			subobject->parrent = this;
			subobject->setLevel(level);
		}
	}

	void Entity::AttachTo(Entity* parrent)
	{
		if (parrent != nullptr)
		{
			this->parrent = parrent;
			parrent->subobjects.append(this);
			setLevel(parrent->level);
		}
	}

	Entity& Entity::operator<<(Entity* child)
	{
		AttachSubobject(child);
		return *this;
	}

	const QList<Entity*>& Entity::getSubobjects()
	{
		return subobjects;
	}

	void Entity::AttachComponent(Component* component)
	{
		if (component != nullptr)
		{
			component->getOwner()->DetachComponent(component);
			component->owner = this;
			components.append(component);
		}
	}

	void Entity::DeleteComponent(Component* component)
	{
		if (component != nullptr)
		{
			components.removeOne(component);
			delete component;
		}
	}

	Entity& Entity::operator<<(Component* component)
	{
		AttachComponent(component);
		return *this;
	}

	void Entity::DetachComponent(Component* component)
	{
		if (component != nullptr)
		{
			components.removeOne(component);
			component->owner = nullptr;
		}
	}

	//QString Entity::toXML()
	//{
	//	QString XMLString = QString(getIndent() + "<Entity name =\"" + name + "\">\n");
	//	increaseIndent();
	//	XMLString += transform.toXML();
	//	for (Component* component : components)
	//	{
	//		//XMLString += component->toXML();
	//	}
	//	for (Entity* subobject : subobjects)
	//	{
	//		XMLString += subobject->toXML();
	//	}
	//	decreaseIndent();
	//	XMLString += QString(getIndent() + "</Entity>\n");
	//
	//	return XMLString;
	//}

	QJsonObject Entity::toJSON()
	{
		QJsonObject JSON = QJsonObject();
		QJsonArray componentsArray = QJsonArray();
		QJsonArray subobjectsArray = QJsonArray();

		for (Component* component : components)
		{
			componentsArray.push_back(component->toJSON());
		}

		for (Entity* subobject : subobjects)
		{
			subobjectsArray.push_back(subobject->toJSON());
		}

		JSON["components"] = componentsArray;
		JSON["subobjects"] = subobjectsArray;

		return JSON;
	}

	IDeserializableFromJSON* Entity::fromJSON(QJsonObject JSON)
	{
		Entity* object = new Entity();

		for (QJsonValueRef componentRef : JSON["components"].toArray())
		{
			QJsonObject componentJSON = componentRef.toObject();

			///TODO: create and attach component.
			//Component* component;
			//
			//object->AttachComponent(component);
		}

		for (QJsonValueRef subobjectRef : JSON["subobjects"].toArray())
		{
			QJsonObject subobjectJSON = subobjectRef.toObject();

			Entity* subobject = static_cast<Entity*>(fromJSON(subobjectJSON));

			object->AttachSubobject(subobject);
		}

		return object;
	}

	void Entity::setLevel(Level* level)
	{
		if (this->level != level)
		{
			this->level = level;
			for (Component* component : components)
			{
				component->levelChanged();
			}
			for (Entity* subobject : subobjects)
			{
				subobject->setLevel(level);
			}
		}
	}
}