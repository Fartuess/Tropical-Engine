#pragma once

class InputManager
{
public:
	static void Update(float time, float cameraSpeed, int* xPos, int* yPos, float g_viewMatrix[16]);	///Handle input
};