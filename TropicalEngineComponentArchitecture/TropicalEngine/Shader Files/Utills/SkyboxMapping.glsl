#ifndef _SKYBOXMAPPING
#define _SKYBOXMAPPING

#include "Utills/SphericalCoordinateSystem.glsl"

#define M_PI 3.1415926535897932384626433832795

vec2 skyBox()
{
	// Assuming that skybox will not be used with elements changing g_eye into TBN space.
	vec3 inSpherical = cartesianToSpherical(g_eye.xzy) / M_PI / vec3(1.0, 1.0, 2.0);// +vec3(0.0, 0.0, 0.5);
	vec2 fixer;
	if (g_eye.x > 0.0)
	{
		fixer = vec2(0.0, 0.0);
	}
	else
	{
		fixer = vec2(0.5, 0.0);
	}

	vec2 newTexcoord = inSpherical.zy + fixer;
	return newTexcoord;
}

#endif