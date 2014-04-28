#pragma once
//#ifndef Scene_Included
//#define Scene_Included

#include "Scene_header.h"

//temp helpers
class Collider;
class AABBCollider;

	extern float zeroTab[3];
	extern float oneTab[3];
	extern GameObject* scene;
	extern Door* Door1;
	extern Door* Door2;

	extern float time;

	//debug
	extern MaterialPoint* mPoint1;

void CreateScene();	///Initializes scene

//#endif //Scene_Included