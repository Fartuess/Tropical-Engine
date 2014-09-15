#include <QtCore\qmap.h>

#include "Component.h"
#include "Entity.h"

Component::Component(Entity* owner)
{
	if(owner != nullptr)
		this->setOwner(owner);
	else
		delete this;
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
		if(this->owner != nullptr)
			this->owner->components.removeOne(this);
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
	parrentComponentTypeMap[getName()] = parrentTypeName;
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
	if(!parameters.contains(getName()))
		parameters[getName()] = QMap<QString, QString>();
	parameters[getName()].insert(name, typeName);
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