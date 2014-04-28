#pragma once

#include "Simulations_header.h"
#include "Scene_header.h"

/*bool Collider::CheckCollision(Collider* collider)
{
	return false;	//temp value? Not sure if all collisions will return false or only those with undefined their own collision methods
}*/

/*
 *	Sphere Collider
 */

SphereCollider::SphereCollider(Vec3 center, float radius)
{
	this->center=center;
	this->radius=radius;
}

SphereCollider::SphereCollider(float x, float y, float z, float radius)
{
	Vec3 center(x,y,z);
	this->radius=radius;
}

bool SphereCollider::CheckCollision(SphereCollider* collider)	//sphere-sphere collision
{
	if( sqrt(pow(center.x - collider->center.x, 2) + pow(center.y - collider->center.y, 2) + pow(center.z - collider->center.z, 2)) < radius+collider->radius)
	{
		return true;
	}
	else
		return false;
}

bool SphereCollider::CheckCollision(AABBCollider* collider)	//sphere-AABB collision
{
	//helpers
	float dFirstY = pow(center.y - collider->firstCorner.y, 2);
	float dSecondY = pow(center.y - collider->secondCorner.y, 2);
	float dFirstZ = pow(center.z - collider->firstCorner.z, 2);
	float dSecondZ = pow(center.z - collider->secondCorner.z, 2);
	float dFirstX = pow(center.x - collider->firstCorner.x, 2);
	float dSecondX = pow(center.x - collider->secondCorner.x, 2);

	if(center.x > collider->firstCorner.x && center.x < collider->secondCorner.x)	//center beetween X
	{
		if(center.y > collider->firstCorner.y && center.y < collider->secondCorner.y)	//center beetween Y
		{
			if(center.z > collider->firstCorner.z && center.z < collider->secondCorner.z)	//center beetween Z
			{
				return true;
			}
			else if(center.z + radius > collider->firstCorner.z	//distance Z
				||  center.z - radius < collider->secondCorner.z)
			{
				return true;
			}
			else return false;
		}
		else if(center.z > collider->firstCorner.z && center.z < collider->secondCorner.z)	//center beetween Z
		{
			if(center.y + radius > collider->firstCorner.y	//distance Y
				||  center.y - radius < collider->secondCorner.y)
			{
				return true;
			}
			else return false;
		}
		else if(sqrt(dFirstY + dFirstZ)<radius	//circle YZ
			||	sqrt(dFirstY + dSecondZ)<radius
			||	sqrt(dSecondY + dFirstZ)<radius
			||	sqrt(dSecondY + dSecondZ)<radius
			)
		{
			return true;
		}
		else return false;
	}
	else if(center.y > collider->firstCorner.y && center.y < collider->secondCorner.y)	//center beetween Y
	{
		if(center.z > collider->firstCorner.z && center.z < collider->secondCorner.z)	//center beetween Z
		{
			if(center.x + radius > collider->firstCorner.x	//distance X
				||  center.x - radius < collider->secondCorner.x)
			{
				return true;
			}
			else return false;
		}
		else if(sqrt(dFirstX + dFirstZ)<radius	//circle XZ
			||	sqrt(dFirstX + dSecondZ)<radius
			||	sqrt(dSecondX + dFirstZ)<radius
			||	sqrt(dSecondX + dSecondZ)<radius
			)
		{
			return true;
		}
		else return false;
	}
	else if(center.z > collider->firstCorner.z && center.z < collider->secondCorner.z)	//center beetween Z
	{
		if(sqrt(dFirstX + dFirstY)<radius	//circle XY
			||	sqrt(dFirstX + dSecondY)<radius
			||	sqrt(dSecondX + dFirstY)<radius
			||	sqrt(dSecondX + dSecondY)<radius
			)
		{
			return true;
		}
		else return true;
	}
	else if(sqrt(dFirstX + dFirstY + dFirstZ) < radius	//spheres x8
		||	sqrt(dFirstX + dFirstY + dSecondZ) < radius
		||	sqrt(dFirstX + dSecondY + dFirstZ) < radius
		||	sqrt(dSecondX + dFirstY + dFirstZ) < radius
		||	sqrt(dFirstX + dSecondY + dSecondZ) < radius
		||	sqrt(dSecondX + dFirstY + dSecondZ) < radius
		||	sqrt(dSecondX + dSecondY + dFirstZ) < radius
		||	sqrt(dSecondX + dSecondY + dSecondZ) < radius
		)
	{
		return true;
	}
	else return false;
}

void SphereCollider::Attach(GameObject* gameObject)
{
	//center=Vec3(*gameObject->Position);
	center=center+*gameObject->Position;
}

/*
 *	AABB Collider
 */

AABBCollider::AABBCollider(Vec3 firstCorner, Vec3 secondCorner)
{
		this->firstCorner.x=min(firstCorner.x, secondCorner.x);
		this->firstCorner.y=min(firstCorner.y, secondCorner.y);
		this->firstCorner.z=min(firstCorner.z, secondCorner.z);

		this->secondCorner.x=max(firstCorner.x, secondCorner.x);
		this->secondCorner.y=max(firstCorner.y, secondCorner.y);
		this->secondCorner.z=max(firstCorner.z, secondCorner.z);
}

AABBCollider::AABBCollider(float firstX, float firstY, float firstZ, float secondX, float secondY, float secondZ)
	{
		firstCorner.x=min(firstX, secondX);
		firstCorner.y=min(firstY, secondY);
		firstCorner.z=min(firstZ, secondZ);

		secondCorner.x=max(firstX, secondX);
		secondCorner.y=max(firstY, secondY);
		secondCorner.z=max(firstZ, secondZ);
	}

bool AABBCollider::CheckCollision(AABBCollider* collider)	//AABB-AABB collision
{
	if((firstCorner.x<collider->secondCorner.x || secondCorner.x>collider->firstCorner.x)
		&&	(firstCorner.y<collider->secondCorner.y || secondCorner.y>collider->firstCorner.y)
		&&	(firstCorner.z<collider->secondCorner.z || secondCorner.z>collider->firstCorner.z)
		)
	{
		return true;
	}
	else
		return false;
}

bool AABBCollider::CheckCollision(SphereCollider* collider)	//AABB-sphere collision
{
	return collider->CheckCollision(this);
}

void AABBCollider::Attach(GameObject* gameObject)
{
	firstCorner=firstCorner+*gameObject->Position;
	secondCorner=secondCorner+*gameObject->Position;
}