#pragma once
#include <QtCore\qjsonobject.h>

#include "Utills\INamedType.h"

class IDeserializableFromJSON : public INamedType
{
public:
	virtual IDeserializableFromJSON& fromJSON(QJsonObject JSON) = 0;
};
