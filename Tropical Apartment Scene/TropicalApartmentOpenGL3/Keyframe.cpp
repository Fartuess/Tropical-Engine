#pragma once

#include "Utility_header.h"
#include "Animations_header.h"

Keyframe::Keyframe(Vec3* position, Vec3* incomingKnot, Vec3* outgoingKnot)
{
	this->position=position;
	this->incomingKnot=incomingKnot;
	this->outgoingKnot=outgoingKnot;
}