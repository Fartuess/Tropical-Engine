#include "Input/InputAction.h"


InputAction::InputAction()
{
	previousFrame = nullptr;
	PressTimestamp = 0;
	ReleaseTimestamp = 0;
	timeHeld = 0;
	updateTime = 0;
	previousFrame = new InputAction(*this);
}

InputAction::~InputAction()
{
	if (previousFrame != nullptr)
	{
		delete previousFrame;
	}
}

InputState InputAction::getState()
{
	return state;
}

int InputAction::getTime(int scriptTime)
{
	if (previousFrame != nullptr)
	{
		updateTime = timer.elapsed();
	}
	int time;
	switch (state)
	{
		case Pressed:
			time = qMin(updateTime - PressTimestamp, qMin(scriptTime, updateTime));
			break;
		case Active:
			time = qMin(updateTime, scriptTime);
			break;
		case Released:
			time = qMax(0, qMin(ReleaseTimestamp, scriptTime - (updateTime - ReleaseTimestamp)));
			break;
		case Inactive:
			time = 0;
			break;
		case MixedPressed:
			if (scriptTime >= updateTime)
			{
				time = timeHeld + (updateTime - PressTimestamp);
			}
			else
			{
				time = qMin(updateTime - PressTimestamp, qMin(scriptTime, updateTime)) + (timeHeld * (scriptTime - (updateTime - ReleaseTimestamp)) / ReleaseTimestamp);
			}
			break;
		case MixedReleased:
			if (scriptTime >= updateTime)
			{
				time = timeHeld;
			}
			else
			{
				time = (timeHeld * (scriptTime - (updateTime - ReleaseTimestamp)) / ReleaseTimestamp);
			}
			break;
		default:
			break;
	}
	if (scriptTime - updateTime > 0 && previousFrame != nullptr)
	{
		time += previousFrame->getTime(scriptTime - updateTime);
	}
	return time;
}

void InputAction::Press()
{
	switch (state)
	{
		case Released:
			state = MixedPressed;
			PressTimestamp = timer.elapsed();
			break;
		case Inactive:
			state = Pressed;
			PressTimestamp = timer.elapsed();
			break;
		case MixedReleased:
			state = MixedPressed;
			PressTimestamp = timer.elapsed();
			break;
		default:
			break;
	}
}

void InputAction::Release()
{
	switch (state)
	{
		case Pressed:
			state = MixedReleased;
			ReleaseTimestamp = timer.elapsed();
			timeHeld = ReleaseTimestamp - PressTimestamp;
			break;
		case Active:
			state = Released;
			ReleaseTimestamp = timer.elapsed();
			break;
		case MixedPressed:
			state = MixedReleased;
			ReleaseTimestamp = timer.elapsed();
			timeHeld += ReleaseTimestamp - PressTimestamp;
			break;
		default:
			break;
	}
}

void InputAction::Update()
{
	updateTime = timer.elapsed();
	if (previousFrame != nullptr)
	{
		delete previousFrame;
	}
	previousFrame = new InputAction(*this);
	previousFrame->previousFrame = nullptr;
	PressTimestamp = 0;
	ReleaseTimestamp = 0;
	timeHeld = 0;
	updateTime = 0;
	timer.restart();
	
	switch (state)
	{
		case Pressed:
			state = Active;
			break;
		case Released:
			state = Inactive;
			break;
		case MixedPressed:
			state = Active;
			break;
		case MixedReleased:
			state = Inactive;
			break;
		default:
			break;
	}
}
