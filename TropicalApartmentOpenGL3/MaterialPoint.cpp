#pragma once

#include "Simulations_header.h"

/*
 *  NOTE: Runge-Kutta isn't done yet.
 */

MaterialPoint::MaterialPoint(Vec3 value, float mass) : Value(value), Mass(mass)
{
	Acceleration=new Vec3(Vec3Zero);
	Velocity=new Vec3(Vec3Zero);

	PhysicsManager::addMaterialPoint(this);
}

void MaterialPoint::setGameObject(GameObject* object)
{
	this->object=object;
}

MaterialPoint::MaterialPoint(Vec3 value, float mass, GameObject* object) : Value(value), Mass(mass)
{
	Acceleration=new Vec3(Vec3Zero);
	Velocity=new Vec3(Vec3Zero);

	PhysicsManager::addMaterialPoint(this);

	setGameObject(object);
}

void MaterialPoint::addVelocity(Vec3* velocity)
{
	*Velocity=*Velocity+*velocity;
}

void MaterialPoint::addAcceleration(Vec3* acceleration)
{
	*Acceleration=*Acceleration+*acceleration;
}

void MaterialPoint::addForce(Vec3* force)
{
	//acceleration=Vec3(acceleration.x+(force->x/mass), acceleration.y+(force->y/mass), acceleration.z+(force->z/mass));
	*Velocity=*Velocity+(*force/Mass);
}

void MaterialPoint::simulate(float deltaTime)
{
	simulateEuler(deltaTime);
}

void MaterialPoint::simulateEuler(float deltaTime)
{
	*Velocity=*Velocity+(*Acceleration*deltaTime);
	Vec3 prevValue(Value);
	Value=Value+(*Velocity*deltaTime);
	if(CollisionManager::checkWithAllCollisions(this->object->collider)==true)
	{
		Value=prevValue;
	}
}

void MaterialPoint::simulateRungeKutta(float deltaTime)
{
	Vec3 k1;
	Vec3 k2;
	Vec3 k3;
	Vec3 k4;
	Value = Value+(k1 + k2*2.0f + k3*2.0f + k4);
}