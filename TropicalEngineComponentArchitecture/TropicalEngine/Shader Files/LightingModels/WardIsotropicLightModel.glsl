#ifndef _WARDISOTROPICLIGHTINGMODEL
#define _WARDISOTROPICLIGHTINGMODEL

#define M_PI 3.1415926535897932384626433832795

#define DIFFUSEINPUT
vec3 g_diffuseInput = vec3(0.5, 0.5, 0.5);

#define SPECULARINPUT
vec3 g_specularInput = vec3(0.5, 0.5, 0.5);

#define ROUGHNESSINPUT
float g_roughnessInput = 0.5;

//private
void calculateWardIsotropic(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float roughness, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
	vec3 h = normalize(lightVector + eye);

	// Generate any useful aliases
	float VdotN = dot(eye, normal);
	float LdotN = dot(lightVector, normal);
	float HdotN = dot(h, normal);
	float roughness_squared = (roughness * roughness) + 0.0001;
	// (Adding a small bias to r_sq stops unexpected
	//  results caused by divide-by-zero)

	// Define material properties
	vec3 Ps = vec3(1.0, 1.0, 1.0);

	// Compute the specular term
	float exp_a;

	// manually compute the complex term
	exp_a = -pow(tan(acos(HdotN)), 2);
	//}
	float spec_num = exp(exp_a / roughness_squared);

	float spec_den = 4.0 * M_PI * roughness_squared;
	spec_den *= sqrt(LdotN * VdotN);

	vec3 Specular = Ps * (spec_num / spec_den);

	// Composite the final value:
	diffuseIntensity += max(0, dot(normal, lightVector)) * lightColor * brightness;
	specularIntensity += max(vec3(0.0f), Specular) * lightColor * brightness * max(0, dot(normal, lightVector));

}

/**
* Common interface for calculating lighting models.
*/
void calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness)
{
	calculateWardIsotropic(lightVector, lightColor, lightBrightness, g_normal, g_eye, g_roughnessInput, g_diffuseChannel, g_specularChannel);
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