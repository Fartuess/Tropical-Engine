#ifndef _COOKTORRANCELIGHTINGMODEL
#define _COOKTORRANCELIGHTINGMODEL

#define M_PI 3.1415926535897932384626433832795

#define DIFFUSEINPUT
vec3 g_diffuseInput = vec3(0.5, 0.5, 0.5);

#define SPECULARINPUT
vec3 g_specularInput = vec3(0.5, 0.5, 0.5);

#define ROUGHNESSINPUT
float g_roughnessInput = 0.5;

#define REFRACITVEINDEXINPUT
float g_refractiveIndexInput = 0.15;

#define DIFFUSECHANNEL
vec3 g_diffuseChannel;
#define SPECULARCHANNEL
vec3 g_specularChannel;

//private
void calculateCookTorrance(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float roughness, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		vec3 H = (lightVector + eye) / length(lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);

		float alphaDegree = acos(nDotH);
		float beckmanDistribution = exp(-pow(tan(alphaDegree), 2) / pow(roughness, 2)) / (M_PI * pow(roughness, 2) * pow(cos(alphaDegree), 4));

		//schlick's approximation of fresnel
		float R = pow((1 - mat_refractiveIndex) / (1 + mat_refractiveIndex), 2);
		float eDotH = max(dot(eye, H), 0);
		float fresnel = R + (1 - R) * pow(cos(eDotH), 5);

		float geometric = min(1.0, min(2.0 * nDotH * dot(normal, eye) / eDotH, (2 * dot(normal, H) * nDotL) / eDotH));

		float spec = (fresnel * geometric * beckmanDistribution) / (dot(normal, eye) * M_PI);

		diffuseIntensity += lightColor * brightness * nDotL;
		specularIntensity += lightColor * brightness * spec;
	}
}

/**
* Common interface for calculating lighting models.
*/
void calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness)
{
	calculateCookTorrance(lightVector, lightColor, lightBrightness, g_normal, g_eye, g_roughnessInput, g_diffuseChannel, g_specularChannel);
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