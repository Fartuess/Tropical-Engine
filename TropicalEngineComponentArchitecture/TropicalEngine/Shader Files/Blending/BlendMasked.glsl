#ifndef _BLENDMASKED
#define _BLENDMASKED

#define BLENDMASKED

uniform float mat_maskThreshold = 0.3333;

#define MASKINPUT
float g_maskInput = 1.0;

void blend()
{
	if (g_maskInput < mat_maskThreshold)
	{
		discard;
	}
	FragColor = vec4(color, 1.0);
}

#endif