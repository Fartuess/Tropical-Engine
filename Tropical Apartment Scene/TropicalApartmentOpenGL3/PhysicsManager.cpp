#pragma once

#include "Simulations_header.h"

list<MaterialPoint*> PhysicsManager::materialPoints;

void PhysicsManager::addMaterialPoint(MaterialPoint* materialPoint)
{
	materialPoints.push_back(materialPoint);
}

void PhysicsManager::simulateAll(float deltaTime)
{
	for( list<MaterialPoint*>::iterator iter=materialPoints.begin(); iter != materialPoints.end(); ++iter )
	{
		(*iter)->simulate(deltaTime);
	}
}
