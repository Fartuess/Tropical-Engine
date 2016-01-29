#pragma once
#include <QtCore/qstring.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Interface for named types.
	  */
	#pragma endregion
	class INamedType
	{
	public:
		#pragma region documentation
		/**
		  * \brief Gets name of the type of objects. Every type implementing this interface should implement this method.
		  *
		  * @return Name of the type.
		  */
		#pragma endregion
		virtual QString getTypeName() = 0;
	};

	#pragma region documentation
	/**
	  * \brief Macro for quick implementing of getTypeName.
	  *
	  * @param name Name of type.
	  */
	#pragma endregion
	#define TYPENAME(name)\
	inline QString getTypeName() override\
		{\
		return #name;\
		}

}