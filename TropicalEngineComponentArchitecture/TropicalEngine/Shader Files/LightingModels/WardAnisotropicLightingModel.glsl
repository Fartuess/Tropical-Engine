#ifndef _WARDANISOTROPICLIGHTINGMODEL
#define _WARDANISOTROPICLIGHTINGMODEL

#include "Lighting/LightingResult.glsl"

#define TANGENTSPACE

#define M_PI 3.1415926535897932384626433832795

#define DIFFUSEINPUT
vec3 g_diffuseInput = vec3(0.5, 0.5, 0.5);

#define SPECULARINPUT
vec3 g_specularInput = vec3(0.5, 0.5, 0.5);

#define ANISOROUGHNESSINPUT
vec2 g_anisoRoughnessInput = vec2(0.5);

//private
LightingResult calculateWardAnisotropic(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 tangent, in vec3 bitangent, in vec3 eye, in vec2 anisoRoughness)
{
	vec3 h = normalize(lightVector + eye);
	// Generate any useful aliases
	float VdotN = dot(eye, normal);
	float LdotN = dot(lightVector, normal);
	float HdotN = dot(h, normal);
	float HdotT = dot(h, tangent);
	float HdotB = dot(h, bitangent);

	// Evaluate the specular exponent
	float beta_a = HdotT / anisoRoughness.x;
	beta_a *= beta_a;

	float beta_b = HdotB / anisoRoughness.y;
	beta_b *= beta_b;

	float beta = -2.0 * ((beta_a + beta_b) / (1.0 + HdotN));

	// Evaluate the specular denominator
	float s_den = 4.0 * M_PI;
	s_den *= anisoRoughness.x;
	s_den *= anisoRoughness.y;
	s_den *= sqrt(LdotN * VdotN);

	// Compute the final specular term
	float Specular = /*Ps * */ (exp(beta) / s_den);

	// Composite the final value:

	LightingResult lightingResult = LightingResult(vec3(0.0), vec3(0.0));
	lightingResult.diffuse = max(0, dot(normal, lightVector)) * lightColor * brightness;
	lightingResult.specular = max(0.0f, Specular) * lightColor * brightness * max(0, dot(normal, lightVector));
	return lightingResult;
}

/**
* Common interface for calculating lighting models.
*/
LightingResult calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 eye)
{
	return calculateWardAnisotropic(lightVector, lightColor, lightBrightness, g_normal, g_tangent, g_bitangent, eye, g_anisoRoughnessInput);
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