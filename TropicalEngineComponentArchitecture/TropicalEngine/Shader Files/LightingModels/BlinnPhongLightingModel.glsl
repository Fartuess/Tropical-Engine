#ifndef _BLINNPHONGLIGHTINGMODEL
#define _BLINNPHONGLIGHTINGMODEL

#include "Lighting/LightingResult.glsl"

#define DIFFUSEINPUT
vec3 g_diffuseInput = vec3(0.5, 0.5, 0.5);

#define SPECULARINPUT
vec3 g_specularInput = vec3(0.5, 0.5, 0.5);

#define SPECULAREXPONENTINPUT
float g_specularExponentInput = 1.0;

#define DIFFUSECHANNEL
vec3 g_diffuseChannel;
#define SPECULARCHANNEL
vec3 g_specularChannel;

//private
LightingResult calculateBlinnPhong(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float specularExponent)
{
	LightingResult lightingResult = LightingResult(vec3(0.0), vec3(0.0));
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		vec3 reflection = reflect(-lightVector, normal);
		vec3 H = (lightVector + eye) / length(lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);

		lightingResult.diffuse = lightColor * brightness * nDotL;
		lightingResult.specular = lightColor * brightness * pow(nDotH, specularExponent);
	}
	return lightingResult;
}

/**
* Common interface for calculating lighting models.
*/
LightingResult calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 eye)
{
	return calculateBlinnPhong(lightVector, lightColor, lightBrightness, g_normal, eye, g_specularExponentInput);
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
	g_color += g_lightingResult.specular * g_specularInput;
}

#endif