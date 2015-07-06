#pragma once
#include <QtCore/qstring.h>

class ISerializableToXML
{
public:
	virtual QString toXML() = 0;

	static void resetIndent();
	static void increaseIndent();
	static void decreaseIndent();
	static int getIndentLevel();
	static QString getIndent();

private:
	static int indentLevel;
};

