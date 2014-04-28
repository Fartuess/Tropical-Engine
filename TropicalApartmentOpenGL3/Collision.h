#pragma once
//#ifndef Collision_Included
//#define Collision_Included

#include "Animations_header.h"
#include "Simulations_header.h"

class GameObject;
class AABBCollider;
class SphereCollider;

class Collider
{
public:
	bool virtual CheckCollision(Collider* collider) = 0;	///Checks if collision happened
	//bool virtual CheckCollision(SphereCollider* collider)=0;
	//bool virtual CheckCollision(AABBCollider* collider)=0;

	void virtual Attach(GameObject* gameObject) = 0;	///Attach collider to given Game Object
};


class SphereCollider:Collider
{
public:
	Vec3 center;
	float radius;

	SphereCollider(Vec3 center, float radius);
	SphereCollider(float x, float y, float z, float radius);

	//bool CheckCollision(Collider* collider);
	bool CheckCollision(SphereCollider* collider);
	bool CheckCollision(AABBCollider* collider);

	void Attach(GameObject* gameObject);
};

class AABBCollider:Collider
{
public:
	Vec3 firstCorner;
	Vec3 secondCorner;

	AABBCollider(Vec3 firstCorner, Vec3 secondCorner);
	AABBCollider(float firstX, float firstY, float firstZ, float secondX, float secondY, float secondZ);

	//bool CheckCollision(Collider* collider);
	bool CheckCollision(SphereCollider* collider);
	bool CheckCollision(AABBCollider* collider);

	void Attach(GameObject* gameObject);
};

//#endif //Collision_Included