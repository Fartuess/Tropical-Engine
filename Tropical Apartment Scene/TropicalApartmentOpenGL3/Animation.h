#pragma once
//#ifndef Animation_Included
//#define Animation_Included

#include "Utility_header.h"
#include "Animations_header.h"
#include <list>
#include <map>

class Animation
{
	double currentTime;
	float currentSpeed;//usage not implemented yet
	bool direction;//usage not implemented yet
	bool isLooped;
	std::map<float, Keyframe*> animation;
	
public:
	Vec3 value;
	Animation();
	//Animation(bool isLooped);
	//Animation(bool direction, bool isLooped, float speed);

	void AddKeyframe(float time, Keyframe* keyframe);	///Add's animation keyframe

	//void StartAnimation();
	//void StartAnimation(bool isLooped=false);
	//void StartAnimation(bool isLooped, bool isForward);
	//void StartAnimation(float speedMultiplier);
	//void StartAnimation(bool isForward, float speedMultiplier);

	void StartAnimation(bool isLooped=false, bool isForward=true, float speedMultiplier=1.0f);	///Starts Animation

	Vec3 Bezier(Keyframe* keyframe1, Keyframe* keyframe2, float fraction);	///Get position at given time from bezier curve
	void PlayAnimation(float deltatime);	///Updates position
};

class AnimationManager
{
public:
	
	static std::list<Animation*>animations;

	static void PlayAllAnimations(float deltatime);	///Updates position of all animated objects
};

//#endif //Animation_Included