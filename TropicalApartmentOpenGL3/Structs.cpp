#pragma once

#include "Utility_header.h"

Vec3::Vec3()
{

}


Vec3::Vec3(float X, float Y, float Z)
	{
		x=X;
		y=Y;
		z=Z;
	}

Vec3 Vec3::operator+(Vec3 &param)
{
	Vec3 temp;
	temp.x=param.x+x;
	temp.y=param.y+y;
	temp.z=param.z+z;
	return temp;
}

Vec3 Vec3::operator*(Vec3 &param)
{
	x*=param.x;
	y*=param.y;
	z*=param.z;
	return *this;
}

Vec3 Vec3::operator*(const float &param)
{
	Vec3 temp;
	temp.x=x*param;
	temp.y=y*param;
	temp.z=z*param;
	return temp;
}

Vec3 Vec3::operator/(const float &param)
{
	Vec3 temp;
	temp.x=x/param;
	temp.y=y/param;
	temp.z=z/param;
	return temp;
}

Vec3 Vec3::LerpVec3(Vec3* first, Vec3* second, float fractiontime)
{
	Vec3 interpolatedVec3((first->x*(1.0f-fractiontime))+(second->x*fractiontime), (first->y*(1.0f-fractiontime))+(second->y*fractiontime), (first->z*(1.0f-fractiontime))+(second->z*fractiontime));
	return interpolatedVec3;
}

Vec3 Vec3Zero = Vec3(0.0f, 0.0f, 0.0f);
Vec3 Vec3One = Vec3(1.0f, 1.0f, 1.0f);

Vec2::Vec2(float X, float Y)
{
	x = X;
	y = Y;
}

Vec4::Vec4(float X, float Y, float Z, float W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}