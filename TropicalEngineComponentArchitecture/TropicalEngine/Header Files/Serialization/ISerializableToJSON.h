#pragma once
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include <Utills/INamedType.h>

/**
  * Interface for Serialization objects to JSON.
  */
class ISerializableToJSON : virtual public INamedType
{
public:
	/**
	  * \brief Serializes object into JSON.
	  *
	  * @return Result of serialization.
	  */
	virtual QJsonObject toJSON() = 0;
};