#pragma once
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include <Utills/INamedType.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * Interface for Serialization objects to JSON.
	  */
#	pragma endregion
	class ISerializableToJSON : virtual public INamedType
	{
	public:
		#pragma region documentation
		/**
		  * \brief Serializes object into JSON.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		virtual QJsonObject toJSON() = 0;
	};

}