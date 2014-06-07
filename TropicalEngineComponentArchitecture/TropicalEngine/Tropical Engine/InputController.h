#pragma once
#include <glm.hpp>
#include "CameraComponent.h"
#include "singleton.h"
class InputController// :
	//public Singleton<InputController>
{
	struct keyState
	{
		bool W, A, S, D, SPACE, C, UP, LEFT, DOWN, RIGHT;
	};
public:
	glm::vec2 lastMousePosition;
	glm::vec2 mousePosition;
	keyState pressedKeys;

	InputController(void);
	~InputController(void);

	void Update();
};