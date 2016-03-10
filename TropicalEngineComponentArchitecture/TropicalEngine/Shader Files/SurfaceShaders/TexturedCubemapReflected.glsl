#ifndef _TEXTUREDCUBEMAPREFLECTED
#define _TEXTUREDCUBEMAPREFLECTED

uniform samplerCube mat_color;

#ifndef EMISSIVEINPUT
#define EMISSIVEINPUT
uniform vec3 mat_emissive = vec3(0.0);
vec3 g_emissiveInput = vec3(0.0);
#endif

void processSurface()
{
	vec3 reflection = reflect(-g_eye, g_normal);

	g_emissiveInput = texture(mat_color, reflection).rgb;
}

#endif