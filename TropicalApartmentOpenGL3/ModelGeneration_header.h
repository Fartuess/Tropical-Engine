#pragma once

#include "Utility_header.h"
#include "Models_header.h"

class ModelGenerator
{
public:
	static GLUSshape* generateTriangle();

	static GLUSshape* generatePlane(float sizeX, float sizeY, int subdivisionsX, int subdivisionsY);

	static GLUSshape* generateCube(Vec3 size, Vec3 subdivisions);
	static GLUSshape* generateCube(Vec3 size, int subdivisionsX, int subdivisionsY, int subdivisionsZ);
	static GLUSshape* generateCube(float sizeX, float sizeY, float sizeZ, int subdivisionsX, int subdivisionsY, int subdivisionsZ);

	static GLUSshape* generateSphere(float radius, int subdivisionsAxis, int subdivisionsHeight);

	static GLUSshape* generateCylinder(float radius, float height, int subdivisiomsAxis, int subdivisionsHeight);

	static GLUSshape* generateCone(float radius, float height, int subdivisionsAxis, int subdivisionsHeight);

	static GLUSshape* generateTorus(float radius, float segmentRadius, int subdivisionsAxis, int subdivisionsHeight);
};