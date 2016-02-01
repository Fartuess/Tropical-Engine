#ifndef _CUBEMAPREFLECTION
#define _CUBEMAPREFLECTION

#include "Utills/SphericalCoordinateSystem.glsl"

#define M_PI 3.1415926535897932384626433832795

// Tmporarily will use phong reflection?
vec2 cubemapReflection()
{
	vec3 reflection = reflect(-g_eye, g_normal);

	vec3 inSpherical = cartesianToSpherical(reflection.xzy * vec3(1.0, 1.0, -1.0)) / M_PI / vec3(1.0, 1.0, 2.0);

	vec2 fixer;
	if (reflection.x > 0)
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