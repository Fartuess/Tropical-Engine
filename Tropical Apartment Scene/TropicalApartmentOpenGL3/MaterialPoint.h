#pragma once
//#ifndef MaterialPoint_Included
//#define MaterialPoint_Included

#include "Simulations_header.h"
#include "Scene_header.h"

class GameObject;

class MaterialPoint
{
private:
	Vec3* Velocity;
	Vec3* Acceleration;
	float Mass;
public:
	GameObject* object;

	Vec3 Value;
	MaterialPoint(Vec3 value, float mass);
	MaterialPoint(Vec3 value, float mass, GameObject* object);
	void setGameObject(GameObject* object);	///Attach Game Object to this Material Point
	void addVelocity(Vec3* velocity);	///Adds Velocity
	void addAcceleration(Vec3* acceleration);	///Adds Acceleration
	void addForce(Vec3* force); ///Adds Force
	void simulate(float deltaTime);	///Updates simulation
	void simulateEuler(float deltaTime);	///Updates simulation using Euler method
	void simulateRungeKutta(float deltaTime);	///Updates simulation using Runge-Kutta method - TO BE IMPLEMENTED!
};

//#endif // MaterialPoint_Included