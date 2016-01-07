#ifndef _PHONGLIGHTINGMODEL
#define _PHONGLIGHTINGMODEL

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
void calculatePhong(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 normal, in vec3 eye, float specularExponent, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-lightVector, normal);
		float eDotR = max(dot(eye, reflection), 0.0);

		diffuseIntensity += lightColor * lightBrightness *  nDotL;
		specularIntensity += lightColor * lightBrightness * pow(eDotR, specularExponent);
	}
}

/**
  * Common interface for calculating lighting models.
  */
void calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness)
{
	calculatePhong(lightVector, lightColor, lightBrightness, g_normal, g_eye, g_specularExponentInput, g_diffuseChannel, g_specularChannel);
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