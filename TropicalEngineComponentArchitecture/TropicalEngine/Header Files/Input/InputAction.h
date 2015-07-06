#pragma once

#include <QtCore/qtime>

enum InputState
{
	Pressed,
	Active,
	Released,
	Inactive,
	MixedPressed,
	MixedReleased
};

class InputAction
{
public:
	InputAction();

	~InputAction();

	InputState getState();
	int getTime(int scriptTime);

	void Press();
	void Release();
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
