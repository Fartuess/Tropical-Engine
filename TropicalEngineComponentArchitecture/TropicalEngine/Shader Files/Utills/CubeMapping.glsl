#ifndef _CUBEMAPPING
#define _CUBEMAPPING

#include "Utills/SphericalCoordinateSystem.glsl"

#define M_PI 3.1415926535897932384626433832795

vec2 cubemap()
{
	vec3 inSpherical = cartesianToSpherical(g_normal.xzy * vec3(1.0, 1.0, -1.0)) / M_PI / vec3(1.0, 1.0, 2.0);

	vec2 fixer;
	if (g_normal.x > 0)
	{
		fixer = vec2(0.5, 0.0);
	}
	else
	{
		fixer = vec2(0.0, 0.0);
	}

	vec2 newTexcoord = inSpherical.zy + fixer;
	return newTexcoord;
}

#endif