#include "Serialization/ISerializableToXML.h"

int ISerializableToXML::indentLevel;

void ISerializableToXML::resetIndent()
{
	indentLevel = 0;
}

void ISerializableToXML::increaseIndent()
{
	indentLevel++;
}

void ISerializableToXML::decreaseIndent()
{
	indentLevel--;
}

int ISerializableToXML::getIndentLevel()
{
	return indentLevel;
}

QString ISerializableToXML::getIndent()
{
	QString indent = "";
	for(int i = 0; i < indentLevel; i++)
	{
		indent += "\t";
	}
	return indent;
}