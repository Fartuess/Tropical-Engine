#ifndef _LAMBERTLIGHTINGMODEL
#define _LAMBERTLIGHTINGMODEL

#include "Lighting/LightingResult.glsl"

#define DIFFUSEINPUT
vec3 g_diffuseInput = vec3(0.5, 0.5, 0.5);

#define DIFFUSECHANNEL
vec3 g_diffuseChannel;

#line 20000

//private
LightingResult calculateLambert(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 normal)
{
	LightingResult lightingResult = LightingResult(vec3(0.0), vec3(0.0));

	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		lightingResult.diffuse = lightColor * lightBrightness *  nDotL;
	}
	return lightingResult;
}

/**
* Common interface for calculating lighting models.
*/
LightingResult calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 eye)
{
	return calculateLambert(lightVector, lightColor, lightBrightness, g_normal);
}

/**
* Calculates final color for given lighting model.
*/
void finalizeLightingModel()
{
#ifdef AMBIENTCHANNEL
	g_color += g_ambientChannel * g_diffuseInput;
#endif
	g_color += g_lightingResult.diffuse * g_diffuseInput;
}

#endif