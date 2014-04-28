#pragma once
//#ifndef PhysicsManager_Included
//#define PhysicsManager_Included


#include "Simulations_header.h"

class PhysicsManager
{
	

public:
	static list<MaterialPoint*> materialPoints;
	static void addMaterialPoint(MaterialPoint* materialPoint);	///Adds new Material Point
	static void simulateAll(float deltaTime);	///Updates all Material Points
};

//#endif // PhysicsManager_Included