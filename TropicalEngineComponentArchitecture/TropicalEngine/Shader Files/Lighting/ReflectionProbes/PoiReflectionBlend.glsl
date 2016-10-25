#ifndef _POIREFLECTIONBLEND
#define _POIREFLECTIONBLEND

#define TEXTURECOORDINATES

//struct ReflectionProbe
//{
//	sampler2D texture;
//	float strength;
//};
//// temporarily shader is treated as material shader and not engine shader.
//uniform ReflectionProbe mat_reflectionProbes[3];

uniform sampler2D mat_RPtex0;
uniform sampler2D mat_RPtex1;
uniform sampler2D mat_RPtex2;

uniform float mat_RPstr0;
uniform float mat_RPstr1;
uniform float mat_RPstr2;


#ifndef EMISSIVEINPUT
#define EMISSIVEINPUT
uniform sampler2D mat_emissive;	//ignored
uniform bool mat_usesEmissive = true;	//ignored?
vec3 g_emissiveInput = vec3(0.0);
#endif

float strenghtSum()
{
	float sum = 0.0;

	sum += mat_RPstr0;
	sum += mat_RPstr1;
	sum += mat_RPstr2;

	return sum;
}

vec3 colorSum()
{
	vec3 blendedColor = vec3(0.0);

	blendedColor += (texture(mat_RPtex0, g_texcoord).rgb * mat_RPstr0);
	blendedColor += (texture(mat_RPtex1, g_texcoord).rgb * mat_RPstr1);
	blendedColor += (texture(mat_RPtex2, g_texcoord).rgb * mat_RPstr2);

	return blendedColor;
}


void processSurface()
{
#ifdef EMISSIVEINPUT

	float strengthSum = strenghtSum();

	vec3 blendedColor = colorSum();

	if (strengthSum > 1.0)
	{
		blendedColor /= strengthSum;
	}

	g_emissiveInput = blendedColor;

	//g_emissiveInput = vec3(mat_reflectionProbes[0].strength, 0.0, 0.0);

	//g_emissiveInput = texture(mat_reflectionProbes[2].texture, g_texcoord).rgb;

#endif
}

#endif