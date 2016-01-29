#pragma once

#include <QtCore/qstring.h>
#include <QtCore/qdebug.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Base template class for exceptions.
	  */
	#pragma endregion
	template <class T> class Exception
	{
	public:
		#pragma region documentation
		/**
		  * \brief Object which thrown the exception.
		  */
		#pragma endregion
		T* throwingObject;

		#pragma region documentation
		/**
		  * \brief Error message.
		  */
		#pragma endregion
		QString message;

		#pragma region documentation
		/**
		  * \brief Constructor for Exception class.
		  *
		  * @param message Error Message.
		  * @param throwingObject Object throwing exception.
		  */
		#pragma endregion
		Exception(QString message, T* throwingObject)
		{
			this->throwingObject = throwingObject;
			this->message = message;
			qDebug() << message;	//Are all exceptions should be written by default or choosen on catching?
		}
		#pragma region documentation
		/**
		  * \brief Deefault destructor.
		  */
		#pragma endregion
		~Exception() {}
	};

}