#pragma once

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Interface for update'able objects.
	  *
	  * Objects of classes implementing this interface are automatically added to UpdateManager and have their onUpdate invoked by it.
	  */
	#pragma endregion
	class IUpdateable
	{
	public:
		#pragma region documentation
		/**
		  * \brief IUpdateable constructor.
		  *
		  * Automatically adds object to UpdateManager.
		  * @param priority Offsets priority of invocation. Lowest value equals earlier invocation??
		  */
		#pragma endregion
		IUpdateable(int priority = 0);
		#pragma region documentation
		/**
		  * \brief IUpdateable destructor.
		  */
		#pragma endregion
		~IUpdateable();

		#pragma region documentation
		/**
		  * \brief Abstract method which will be invoked by UpdateManager every Update.
		  *
		  * @param deltaTime Time since previous Update.
		  */
		#pragma endregion
		virtual void OnUpdate(int deltaTime) = 0;
	};

}