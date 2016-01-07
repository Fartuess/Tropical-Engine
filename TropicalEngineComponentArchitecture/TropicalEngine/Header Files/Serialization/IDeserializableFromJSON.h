#pragma once
#include <QtCore/qjsonobject.h>

#include <Utills/INamedType.h>

namespace TropicalEngine
{

	/**
	  * Interface for deserializing objects from JSON.
	  */
	class IDeserializableFromJSON : virtual public INamedType
	{
	public:
		/**
		  * \brief Creates object from JSON.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Created object.
		  */
		virtual IDeserializableFromJSON* fromJSON(QJsonObject JSON) = 0;
	};

}