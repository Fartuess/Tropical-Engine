#pragma once

#include "Utility_header.h"
#include "Animations_header.h"
#include "Keyframe.h"


using namespace std;
typedef pair <float, Keyframe*> timedKeyframe;


//TODO:		directions, looping and speed should moved to StartAnimation Method

Animation::Animation()
{
	value.x=0;
	value.y=0;
	value.z=0;
	//isLooped=false;
}

/*Animation::Animation(bool isLooped)
{
	value.x=0;
	value.y=0;
	value.z=0;
	this->isLooped=isLooped;
}*/

/*Animation::Animation(bool direction, bool isLooped, float speed)
{
	value.x=0;
	value.y=0;
	value.z=0;
	this->direction=direction;
	this->isLooped=isLooped;
	currentSpeed=speed;
}*/

void Animation::AddKeyframe(float time, Keyframe* keyframe)
{
	animation.insert(timedKeyframe(time, keyframe));
}

/*void Animation::StartAnimation()
{
	currentTime=0;
	currentSpeed=1;
	direction=true;
	isLooped=false;
	AnimationManager::animations.push_back(this);
}*/

void Animation::StartAnimation(bool isLooped, bool isForward, float speedMultiplier)
{
	currentTime=0;
	this->isLooped=isLooped;
	this->direction=isForward;
	this->currentSpeed=speedMultiplier;
	AnimationManager::animations.push_back(this);
}

Vec3 Animation::Bezier(Keyframe* keyframe1, Keyframe* keyframe2, float fraction)
{
	Vec3 sAlpha = sAlpha.LerpVec3(keyframe1->position, keyframe2->position, fraction);
	Vec3 sBeta = sBeta.LerpVec3(keyframe1->outgoingKnot, keyframe2->incomingKnot, fraction);
	float v = 2*fraction*(1-fraction);
	return sAlpha.LerpVec3(&sAlpha, &sBeta, v);
}

void Animation::PlayAnimation(float deltatime)
{
	currentTime+=deltatime*currentSpeed;
	map<float, Keyframe*>::iterator it=animation.end();
	
	if(isLooped==true)
	{
		currentTime=fmod(currentTime, (double)animation.size());
	}
	it--;
	if(it->first>currentTime)
	{
		
		map<float, Keyframe*>::iterator ub=animation.upper_bound(currentTime);
		map<float, Keyframe*>::iterator lb=animation.upper_bound(currentTime);
		lb--;

		//value=value.LerpVec3(&lb->second->position, &ub->second->position, (currentTime - lb->first)/(ub->first - lb->first));
		value=Bezier(lb->second, ub->second, (currentTime - lb->first)/(ub->first - lb->first));
		//use other interpolation algorithm

		//Debug Stuff

		/*
		printf("%f\n", currentTime);
		printf("%f, %f, %f\n", lb->second->position.x, lb->second->position.y, lb->second->position.z);
		printf("%f, %f, %f\n", value.x, value.y, value.z);
		printf("%f, %f, %f\n", ub->second->position.x, ub->second->position.y, ub->second->position.z);
		printf("%f\n", (currentTime - lb->first)/(ub->first - lb->first));
		*/

		//value=value.LerpVec3
	}
}

std::list<Animation*> AnimationManager::animations;

void AnimationManager::PlayAllAnimations(float deltatime)
{
	for( list<Animation*>::iterator iter=animations.begin(); iter != animations.end(); ++iter )
	{
		(*iter)->PlayAnimation(deltatime);
	}
}