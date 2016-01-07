#ifndef _LAMBERTLIGHTINGMODEL
#define _LAMBERTLIGHTINGMODEL

#define DIFFUSEINPUT
vec3 g_diffuseInput = vec3(0.5, 0.5, 0.5);

#define DIFFUSECHANNEL
vec3 g_diffuseChannel;

//private
void calculateLambert(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 normal, inout vec3 diffuseIntensity)
{
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		diffuseIntensity += lightColor * lightBrightness *  nDotL;
	}
}

/**
* Common interface for calculating lighting models.
*/
void calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness)
{
	calculateLambert(lightVector, lightColor, lightBrightness, g_normal, g_diffuseChannel);
}

/**
* Calculates final color for given lighting model.
*/
void finalizeLightingModel()
{
#ifdef AMBIENTCHANNEL
	g_color += g_ambientChannel * g_diffuseInput;
#endif
	g_color += g_diffuseChannel * g_diffuseInput;
}

#endif