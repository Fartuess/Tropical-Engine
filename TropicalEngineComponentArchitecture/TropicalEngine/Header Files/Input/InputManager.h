#pragma once
#include <glm.hpp>

#include <QtCore/qhash.h>
#include <QtWidgets/qaction.h>

#include <Camera/CameraComponent.h>

#include <Utills/Singleton.h>

#include "InputAction.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing inputs.
	  */
	#pragma endregion
	class InputManager : public Singleton<InputManager>
	{
	public:
		#pragma region documentation
		/**
		  * \brief Position of mouse before last Update.
		  */
		#pragma endregion
		glm::vec2 lastMousePosition;
		#pragma region documentation
		/**
		  * \brief Current mouse position.
		  */
		#pragma endregion
		glm::vec2 mousePosition;

		#pragma region documentation
		/**
		  * \brief InputManager constructor.
		  */
		#pragma endregion
		InputManager(void);
		#pragma region documentation
		/**
		  * \brief InputManager destructor.
		  */
		#pragma endregion
		~InputManager(void);

		#pragma region documentation
		/**
		  * \brief Notifies InputManager about physical key being pressed.
		  *
		  * @param key Id of physical key. int used instead Qt::Key enum for potential support of other controller unsupported by Qt itself.
		  */
		#pragma endregion
		void PressKey(int key);
		#pragma region documentation
		/**
		  * \brief Notifies InputManager about physical key being released.
		  *
		  * @param key Id of physical key. int used instead Qt::Key enum for potential support of other controller unsupported by Qt itself.
		  */
		#pragma endregion
		void ReleaseKey(int key);

		#pragma region documentation
		/**
		  * \brief Private used by engine to update mouse position info and all InputActions
		  */
		#pragma endregion
		void Update();

		#pragma region documentation
		/**
		  * \brief Creates new InputAction unbound to any physical key.
		  *
		  * @param actionName Name for new InputAction.
		  */
		#pragma endregion
		void AddAction(QString actionName);
		#pragma region documentation
		/**
		  * \brief Creates new InputAction and binds it to physical key.
		  *
		  * @param actionName Name for new InputAction.
		  * @param key Id of physical key. int used instead Qt::Key enum for potential support of other controller unsupported by Qt itself.
		  */
		#pragma endregion
		void AddAction(QString actionName, int key);
		#pragma region documentation
		/**
		  * \brief Binds key to InputAction.
		  *
		  * InputAction with said name doesn't have to exist yet?
		  * @param actionName Name of InputAction to bind.
		  * @param key Id of physical key. int used instead Qt::Key enum for potential support of other controller unsupported by Qt itself.
		  */
		#pragma endregion
		void BindAction(QString actionName, int key);
		// TODO: Add unbinding keys method for InputManager?

		#pragma region documentation
		/**
		  * \brief Gets current state of asked InputAction.
		  *
		  * @param actionName Name of InputAction.
		  * @return Current state of InputAction.
		  */
		#pragma endregion
		InputState getState(QString actionName);
		#pragma region documentation
		/**
		  * \brief Gets how long InputAction was pressed in probed time.
		  *
		  * @param actionName Name of InputAction.
		  * @param scriptTime Probed time in miliseconds.
		  * @return Time action was pressed in miliseconds.
		  */
		#pragma endregion
		int getTime(QString actionName, int queriedTime);

	private:
		QHash<QString, InputAction*> keyStates;
		QHash<int, QString> bindings;
	};

}