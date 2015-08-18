#include <QtCore/qmap.h>
#include <QtCore/qdebug.h>

#include <Scene/Entity.h>

#include <Component/Component.h>

Component::Component()
{
	owner = nullptr;

}

Component::Component(Entity* owner)
{
	this->owner = nullptr;
	if (owner != nullptr)
	{
		this->setOwner(owner);
	}
	else
	{
		delete this;
	}
}

Component::~Component(void)
{
	if(owner != nullptr)
	{
		owner->DetachComponent(this);
	}
}

Entity* Component::getOwner()
{
	return owner;
}

void Component::setOwner(Entity* owner)
{
	
	if(owner != nullptr)
	{
		if (this->owner != nullptr)
		{
			//qDebug() << this->owner->components.count();
			this->owner->components.removeOne(this);
		}
		this->owner = owner;
		this->owner->components.append(this);
	}
	else
	{
		Detach();
		delete this;
	}
}

void Component::Detach()
{
	owner->components.removeOne(this);
	this->owner = nullptr;
}

QMap<QString, unsigned int> Component::componentTypeMap = QMap<QString, unsigned int>();

void Component::AddComponentType(QString name)
{
	componentTypeMap[name] = componentTypeMap.count();
}

bool Component::isComponentTypeUsed(QString name)
{
	return componentTypeMap.contains(name);
}

unsigned int Component::getComponentType(QString name)
{
	return componentTypeMap[name];
}

QMap<QString, QString> Component::parrentComponentTypeMap = QMap<QString, QString>();

QString Component::getParrentType(QString componentTypeName)
{
	if(parrentComponentTypeMap.contains(componentTypeName))
	{
		return parrentComponentTypeMap[componentTypeName];
	}
	else
	{
		return "";
	}
}

void Component::SetParrentComponentType(QString parrentTypeName)
{
	parrentComponentTypeMap[getTypeName()] = parrentTypeName;
}

QMap<QString, unsigned int> Component::parameterTypeMap = QMap<QString, unsigned int>();

void Component::AddParameterType(QString typeName)
{
	parameterTypeMap[typeName] = parameterTypeMap.count();
}

unsigned int Component::getParameterType(QString typeName)
{
	return parameterTypeMap[typeName];
}

QMap<QString, QMap<QString, QString>> Component::parameters = QMap<QString, QMap<QString, QString>>();

void Component::AddParameter(QString name, QString typeName)
{
	if(!parameterTypeMap.contains(typeName))
		AddParameterType(typeName);
	if (!parameters.contains(getTypeName()))
		parameters[getTypeName()] = QMap<QString, QString>();
	parameters[getTypeName()].insert(name, typeName);
}

QMap<QString, QString> Component::getParameters(QString componentTypeName)
{
	if(parameters.contains(componentTypeName))
	{
		return QMap<QString, QString>(parameters[componentTypeName]).unite(Component::getParameters(getParrentType(componentTypeName)));
	}
	else
	{
		return QMap<QString, QString>();
	}
}

//QString Component::GETTYPENAME("Component");

QJsonObject Component::toJSON()
{
	QJsonObject JSON = QJsonObject();
	JSON["type"] = getTypeName();
	return JSON;
}

QMap<QString, Component*> Component::componentHandles = QMap<QString, Component*>();

IDeserializableFromJSON* Component::fromJSON(QJsonObject JSON)
{
	Component* component = static_cast<Component*>(componentHandles[JSON["type"].toString()]->fromJSON(JSON));

	return component;
}