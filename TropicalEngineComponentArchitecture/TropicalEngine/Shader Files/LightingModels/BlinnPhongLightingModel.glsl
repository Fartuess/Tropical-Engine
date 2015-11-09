#ifndef _BLINNPHONGLIGHTINGMODEL
#define _BLINNPHONGLIGHTINGMODEL

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
void calculateBlinnPhong(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float specularExponent, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		vec3 reflection = reflect(-lightVector, normal);
		vec3 H = (lightVector + eye) / length(lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);

		diffuseIntensity += lightColor * brightness * nDotL;
		specularIntensity += lightColor * brightness * pow(nDotH, specularExponent);
	}
}

/**
* Common interface for calculating lighting models.
*/
void calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness)
{
	calculateBlinnPhong(lightVector, lightColor, lightBrightness, g_normal, g_eye, g_specularExponentInput, g_diffuseChannel, g_specularChannel);
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
	g_color += g_specularChannel * g_specularInput;
}

#endif