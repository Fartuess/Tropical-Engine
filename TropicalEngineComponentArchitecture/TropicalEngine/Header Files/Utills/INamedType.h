#pragma once
#include <QtCore/qstring.h>

/**
  * Interface for named types.
  */
class INamedType
{
public:
	/**
	  * \brief Gets name of the type of objects. Every type implementing this interface should implement this method.
	  *
	  * @return Name of the type.
	  */
	virtual QString getTypeName() = 0;
};

/**
  * \brief Macro for quick implementing of getTypeName.
  *
  * @param name Name of type.
  */
#define TYPENAME(name)\
	inline QString getTypeName() override\
	{\
		return name;\
	}