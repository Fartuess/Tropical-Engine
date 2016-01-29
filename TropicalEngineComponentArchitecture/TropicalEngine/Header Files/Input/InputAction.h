#pragma once
#include <QtCore/qtime>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief States input can be in
	  */
	#pragma endregion
	enum InputState
	{
		Pressed,
		Active,
		Released,
		Inactive,
		MixedPressed,
		MixedReleased
	};

	#pragma region documentation
	/**
	  * \brief InputAction class represents input action without connection to physical input device action like keayboard key press
	  */
	#pragma endregion
	class InputAction
	{
	public:
		#pragma region documentation
		/**
		  * \brief InputAction constructor.
		  */
		#pragma endregion
		InputAction();
		#pragma region documentation
		/**
		  * \brief InputAction destructor.
		  */
		#pragma endregion
		~InputAction();

		#pragma region documentation
		/**
		  * \brief Gets current state of InputAction.
		  *
		  * @return Current state of InputAction.
		  */
		#pragma endregion
		InputState getState();
		#pragma region documentation
		/**
		  * \brief Gets how long action was pressed in probed time.
		  *
		  * @param scriptTime Probed time in miliseconds.
		  * @return Time action was pressed in miliseconds.
		  */
		#pragma endregion
		int getTime(int scriptTime);

		#pragma region documentation
		/**
		  * \brief Press InputAction.
		  */
		#pragma endregion
		void Press();
		#pragma region documentation
		/**
		  * \brief Release InputAction.
		  */
		#pragma endregion
		void Release();
		#pragma region documentation
		/**
		  * \brief Private used by Engine.
		  */
		#pragma endregion
		void Update();

	private:
		InputState state = Inactive;
		QTime timer;
		int PressTimestamp;
		int ReleaseTimestamp;
		int timeHeld;
		int updateTime;
		InputAction* previousFrame;
	};

}