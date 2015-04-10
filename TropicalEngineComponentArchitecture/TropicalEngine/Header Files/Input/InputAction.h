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
private:
	InputState state = Inactive;
	QTime timer;
	int PressTimestamp;
	int ReleaseTimestamp;
	int timeHeld;
	int updateTime;
	InputAction* previousFrame;

public:
	InputAction();
public:
	~InputAction();

	InputState getState();
	int getTime(int scriptTime);

	void Press();
	void Release();
	void Update();
};
