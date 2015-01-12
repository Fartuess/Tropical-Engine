#pragma once
#include <QtCore\qjsonobject.h>
#include <QtCore\qjsonarray.h>

class ISerializableToJSON
{
public:
	virtual QJsonObject toJSON() = 0;
};