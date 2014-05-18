#pragma once

#include "Simulations_header.h"

/*
 *	NOTE: Game object parrent-child collision / collision prevention is not supported yet!
 *
 *	NOTE2: Collision prevention inside colliderGroup is not working yet!
 */

list<Collider*> CollisionManager::colliders;

void CollisionManager::addCollider(Collider* collider)
{
	colliders.push_back(collider);
}

bool CollisionManager::checkWithAllCollisions(Collider* collider)
{
	for( list<Collider*>::iterator iter=colliders.begin(); iter != colliders.end(); ++iter )
	{
		if(collider!=(*iter))	//prevent from colliding with itself
		{
			if(collider->CheckCollision(*iter)==true)	return true;
		}
	}
	return false;
}

bool CollisionManager::checkWithAllCollisions(list<Collider*> colliderGroup)
{
	for( list<Collider*>::iterator iter=colliderGroup.begin(); iter != colliderGroup.end(); ++iter )
	{
		//if(checkWithAllCollisions(*iter)==true)	return true;	//WARNING!! Colliders withing group will be colliding with themselves causing errors!

		for( list<Collider*>::iterator iter2=colliders.begin(); iter2 != colliders.end(); ++iter2 )
		{
			//if((*iter2) not in colliderGroup)	//how to check if object A is on list L?
			{
				if((*iter)->CheckCollision(*iter2)==true)	return true;	//WARNING!! Colliders withing group will be colliding with themselves causing errors! Fix 'if' statement above!
			}
		}
	}
	return false;
}
