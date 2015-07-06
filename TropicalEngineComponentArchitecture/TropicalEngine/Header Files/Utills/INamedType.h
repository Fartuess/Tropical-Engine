#pragma once

#include <QtCore/qstring.h>

class INamedType
{
public:
	virtual QString getTypeName() = 0;
};

#define GETTYPENAME(name)\
	getTypeName()\
	{\
		return name;\
	}