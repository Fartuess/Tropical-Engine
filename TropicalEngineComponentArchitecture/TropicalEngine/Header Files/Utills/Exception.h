#pragma once

#include <QtCore/qstring.h>
#include <QtCore/qdebug.h>

/**
  * Base template class for exceptions.
  */
template <class T> class Exception
{
public:
	/**
	  * \brief Object which thrown the exception.
	  */
	T* throwingObject;

	/**
	  * \brief Error message.
	  */
	QString message;

	/**
	  * \brief Constructor for Exception class.
	  *
	  * @param message Error Message.
	  * @param throwingObject Object throwing exception.
	  */
	Exception(QString message, T* throwingObject)
	{
		this->throwingObject = throwingObject;
		this->message = message;
		qDebug() << message;	//Are all exceptions should be written by default or choosen on catching?
	}

	/**
	  * \brief Deefault destructor.
	  */
	~Exception() {}
};

