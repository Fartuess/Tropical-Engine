#pragma once
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include "Utills/INamedType.h"

class ISerializableToJSON : virtual public INamedType
{
public:
	virtual QJsonObject toJSON() = 0;
};