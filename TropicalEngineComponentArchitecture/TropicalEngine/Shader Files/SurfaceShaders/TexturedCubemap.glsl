#ifndef _TEXTUREDCUBEMAP
#define _TEXTUREDCUBEMAP

uniform samplerCube mat_color;

#ifndef EMISSIVEINPUT
#define EMISSIVEINPUT
uniform vec3 mat_emissive = vec3(0.0);
vec3 g_emissiveInput = vec3(0.0);
#endif

void processSurface()
{
	g_emissiveInput = texture(mat_color, g_normal).rgb;
}

#endif