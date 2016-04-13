#ifndef _CELSHADINGLIGHTINGMODEL
#define _CELSHADINGLIGHTINGMODEL

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

// TODO: Figure out if this should be lighting model or custom lighting module.

LightingResult calculateCelShading(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float specularExponent)
{
	LightingResult lightingResult = LightingResult(vec3(0.0), vec3(0.0));
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		vec3 reflection = reflect(-lightVector, normal);
		vec3 H = (lightVector + eye) / length(lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);
		float nDotHpow = pow(nDotH, specularExponent);

		//if (nDotL > 0.5)
		//{
			lightingResult.diffuse = lightColor * brightness;
		//}
		if (nDotHpow > 0.5)
		{
			lightingResult.specular = lightColor * brightness;
		}
	}
	return lightingResult;
}

/**
* Common interface for calculating lighting models.
*/
LightingResult calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 eye)
{
	return calculateCelShading(lightVector, lightColor, lightBrightness, g_normal, eye, g_specularExponentInput);
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