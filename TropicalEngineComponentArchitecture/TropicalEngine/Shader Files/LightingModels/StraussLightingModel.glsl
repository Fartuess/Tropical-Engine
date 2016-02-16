#ifndef _STRAUSSLIGHTINGMODEL
#define _STRAUSSLIGHTINGMODEL

#include "Lighting/LightingResult.glsl"

#define ALBEDOINPUT
vec3 g_albedoInput = vec3(0.5, 0.5, 0.5);

#define ROUGHNESSINPUT
float g_roughnessInput = 0.5;

#define METALNESSINPUT
float g_metalnessInput = 0.0;

#ifndef AMBIENTCHANNEL
#define AMBIENTCHANNEL
vec3 g_ambientChannel;
#endif
#define DIFFUSECHANNEL
vec3 g_diffuseChannel;
#define SPECULARCHANNEL
vec3 g_specularChannel;

//consts
float roughness_cubed;
float d;
float Rd;
bool constcalculated = false;

//private
void calculateConst()
{
	if (!constcalculated)
	{
		roughness_cubed = g_roughnessInput * g_roughnessInput * g_roughnessInput;
		d = (1.0 - g_metalnessInput * g_roughnessInput);
		Rd = (1.0 - roughness_cubed);

		constcalculated = true;
	}
}

//private
float fresnel(float x)
{
	float kf = 1.12;
	return ((1 / pow(x - kf, 2)) - ((1 / pow(kf, 2)))) / ((1 / pow(1 - kf, 2)) - (1 / pow(kf, 2)));
}

//private
float microfacetShadow(float x)
{
	float kg = 1.01;
	return ((1 / pow(x - kg, 2)) - ((1 / pow(kg, 2)))) / ((1 / pow(1 - kg, 2)) - (1 / pow(kg, 2)));
}

LightingResult calculateStrauss(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, vec3 albedo, float roughness, float metalness)
{
	calculateConst();

	vec3 h = reflect(lightVector, normal);

	// Declare any aliases:
	float NdotL = dot(normal, lightVector);
	float NdotV = dot(normal, eye);
	float HdotV = dot(h, eye);
	float fNdotL = fresnel(NdotL);

	LightingResult lightingResult = LightingResult(vec3(0.0), vec3(0.0));

	if (NdotL > 0.0)
	{
		// Evaluate the diffuse term
		lightingResult.diffuse = NdotL * d * Rd * albedo * lightColor * brightness;

		// Compute the inputs into the specular term
		float r = (1.0) - Rd;

		float j = fNdotL * microfacetShadow(NdotL) * microfacetShadow(NdotV);

		// 'k' is used to provide small off-specular
		// peak for very rough surfaces. Can be changed
		// to suit desired results...
		const float k = 0.1;
		float reflect = min(1.0, r + j * (r + k));

		vec3 vec3_1f = vec3(1.0, 1.0, 1.0);
		vec3 Cs = vec3_1f + metalness * (1.0 - fNdotL) * (albedo - vec3_1f);

		// Evaluate the specular term
		lightingResult.specular = (Cs * reflect * pow(-HdotV, 3.0 / (1.0 - roughness)))  * lightColor * brightness;
	}

	return lightingResult;
}

/**
* Common interface for calculating lighting models.
*/
LightingResult calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 eye)
{
	return calculateStrauss(lightVector, lightColor, lightBrightness, g_normal, g_eye, g_albedoInput, g_roughnessInput, g_metalnessInput);
}

/**
* Calculates final color for given lighting model.
*/
void finalizeLightingModel()
{
#ifdef AMBIENTCHANNEL

	//Overrides default ambient lighting.
	calculateConst();
	g_ambientChannel = (d * Rd * g_albedoInput) * u_lightAmbientColor * u_lightAmbient;

	g_color += g_ambientChannel;
#endif

	g_color += (max(vec3(0.0), g_lightingResult.diffuse) + max(vec3(0.0), g_lightingResult.specular));
}

#endif