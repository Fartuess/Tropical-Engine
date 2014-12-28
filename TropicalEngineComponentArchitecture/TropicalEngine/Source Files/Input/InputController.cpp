#include "Input/InputController.h"

InputController::InputController(void)
{
	lastMousePosition =glm::vec2(0.0f, 0.0f);
	mousePosition = glm::vec2(0.0f, 0.0f);
	pressedKeys.W = false;
	pressedKeys.A = false;
	pressedKeys.S = false;
	pressedKeys.D = false;
	pressedKeys.SPACE = false;
	pressedKeys.C = false;
	pressedKeys.UP = false;
	pressedKeys.LEFT = false;
	pressedKeys.DOWN = false;
	pressedKeys.RIGHT = false;
}

InputController::~InputController(void)
{
	///TODO: implement it.
}

void InputController::Update(int deltaTime)
{
	lastMousePosition = mousePosition;
}
