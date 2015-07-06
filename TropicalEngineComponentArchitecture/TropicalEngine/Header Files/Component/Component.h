#pragma once
#include <QtCore/qmap.h>

#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"
#include "Serialization/IDeserializableFromJSON.h"

#include "Package/AssetManager.h"

class Entity;

class Component : public ISerializableToJSON, public IDeserializableFromJSON
{
public:
	friend class Entity;

	Component(Entity* owner);
	~Component(void);

	Entity* getOwner();
	void setOwner(Entity* owner);

	//virtual QString getName() = 0;
	static bool isComponentTypeUsed(QString name);
	static unsigned int getComponentType(QString name);

	static unsigned int getParameterType(QString name);

	static QMap<QString, QString> getParameters(QString componentTypeName);	//if so change here as well

	//QString getTypeName() = 0;
	QJsonObject toJSON() override;

protected:
	Entity* owner;

	Component();

	virtual void InitializeComponentType() = 0;
	void Detach();
	void AddComponentType(QString name);

	static QString getParrentType(QString componentTypeName);
	void SetParrentComponentType(QString parrentTypeName);

	void AddParameter(QString name, QString type);

private:
	static QMap<QString, unsigned int> componentTypeMap;
	static QMap<QString, QString> parrentComponentTypeMap;

	static QMap<QString, unsigned int> parameterTypeMap;
	static void AddParameterType(QString name);

	static QMap<QString, QMap<QString, QString>> parameters;	//maybe instead of last QString use unsigned int
};