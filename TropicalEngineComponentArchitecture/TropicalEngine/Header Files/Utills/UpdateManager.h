#pragma once
#include <QtCore/qmap.h>
#include <QtCore/qtime>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for Updating scriptable objects.
	  */
	#pragma endregion
	class UpdateManager
	{
	public:
		friend class IUpdateable;

		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		UpdateManager()	{}
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~UpdateManager()	{}

		#pragma region documentation
		/**
		  * \brief Updates all IUpdateable objects.
		  */
		#pragma endregion
		void UpdateAll();
		#pragma region documentation
		/**
		  * \brief Updates specific IUpdateable object.
		  *
		  * @param object IUpdateable object to Update.
		  */
		#pragma endregion
		void Update(class IUpdateable* object);	//it makes mess with delta times

	private:
		QMultiMap<int, IUpdateable*> objects;
		QTime time;
	};

}