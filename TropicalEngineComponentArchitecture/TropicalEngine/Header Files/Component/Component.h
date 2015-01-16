#pragma once
#include <QtCore/qmap.h>

#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"

class Entity;

class Component : public ISerializableToXML, public ISerializableToJSON
{
public:
	friend class Entity;
protected:
	Entity* owner;
public:
	Component(Entity* owner);
	~Component(void);
protected:
	virtual void InitializeComponentType() = 0;
public:
	Entity* getOwner();
	void setOwner(Entity* owner);
protected:
	void Detach();

private:
	static QMap<QString, unsigned int> componentTypeMap;
protected:
	void AddComponentType(QString name);
public:
	virtual QString getName() = 0;
	static bool isComponentTypeUsed(QString name);
	static unsigned int getComponentType(QString name);

//#define ComponentTypeIsInitialized()\
//	componentTypeMap.contains(getName());

private:
	static QMap<QString, QString> parrentComponentTypeMap;
protected:
	static QString getParrentType(QString componentTypeName);
	void SetParrentComponentType(QString parrentTypeName);

//#define COMPONENTPARRENTTYPE(parrentComponent)\
//	getParrentType()\
//	{\
//		return parrentComponent;\
//	}

private:
	static QMap<QString, unsigned int> parameterTypeMap;
	static void AddParameterType(QString name);
public:
	static unsigned int getParameterType(QString name);

private:
	static QMap<QString, QMap<QString, QString>> parameters;	//maybe instead of last QString use unsigned int
protected:
	void AddParameter(QString name, QString type);
public:
	static QMap<QString, QString> getParameters(QString componentTypeName);	//if so change here as well

	QJsonObject toJSON() override;
};

#define COMPONENTGETNAME(name)\
	getName()\
	{\
		return name;\
	}