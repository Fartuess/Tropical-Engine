#pragma once
//#ifndef Keyframe_Included
//#define Keyframe_Included

#include "Models_header.h"
#include "Animations_header.h"

class Keyframe
{
public:
	Vec3* position;
	Vec3* incomingKnot;
	Vec3* outgoingKnot;

	Keyframe(Vec3* position, Vec3* incomingKnot, Vec3* outgoingKnot);
};

//#endif //Keyframe_Included