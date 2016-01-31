#ifndef _CUBEMAPPED
#define _CUBEMAPPED

#include "Utills/CubeMapping.glsl"

uniform sampler2D mat_color;

#ifndef EMISSIVEINPUT
#define EMISSIVEINPUT
uniform vec3 mat_emissive = vec3(0.0);
vec3 g_emissiveInput = vec3(0.0);
#endif

void processSurface()
{
	cubemap();
	g_emissiveInput = texture(mat_color, g_texcoord).rgb;
}

#endif