#pragma once

#include <QtCore/qstring.h>
#include <QtCore/qdebug.h>

template <class T> class Exception
{
public:
	T* throwingObject;

	QString message;

	Exception(QString message, T* throwingObject)
	{
		this->throwingObject = throwingObject;
		this->message = message;
		qDebug() << message;	//Are all exceptions should be written by default or choosen on catching?
	}
	~Exception() {}
};

