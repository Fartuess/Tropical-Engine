#pragma once
//#ifndef CollisionManager_Included
//#define CollisionManager_Included

#include "Simulations_header.h"

class CollisionManager
{
	static list<Collider*> colliders;

public:
	static void addCollider(Collider* collider);	///Adds new collider to manager
	static bool checkWithAllCollisions(Collider* collider);	///Checks given collider with all colliders in manager?
	static bool checkWithAllCollisions(list<Collider*> colliderGroup);	///Checks given set of colliders with all colliders in manager?
};

//#endif //CollisionManager