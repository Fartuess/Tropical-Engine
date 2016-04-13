#ifndef _IMAGEBASEDLIGHTINGCUBEMAP
#define _IMAGEBASEDLIGHTINGCUBEMAP

#include "Lighting/LightingResult.glsl"

#define CUSTOMLIGHTING

uniform samplerCube mat_environmentMap;

LightingResult calculateIBLLighting()
{
	float specularScale = 1.0;

	float diffuseMipMapLevel;
	float specularMipMapLevel;

	diffuseMipMapLevel = 7.25;// max(log2(textureSize(mat_environmentMap, 0).y) - log2(16), 0);

	// TODO: Fix calculation of specularMipMapLevel.

#if defined(ROUGHNESSINPUT)
	specularMipMapLevel = max(log2(textureSize(mat_environmentMap, 0).y) - log2(mix(1024, 16, g_roughnessInput), 0);
	//specularScale = 1.0 - g_roughnessInput;
#elif defined(SPECULAREXPONENTINPUT)
	float helperRough = max(min((1.0 / (g_specularExponentInput / 100.0)), 1.0), 0.0);
	specularMipMapLevel = max(log2(textureSize(mat_environmentMap, 0).y) - log2(mix(8, 1024, helperRough)), 0);
	//specularScale = max(min((g_specularExponentInput / 100.0), 1.0), 0.0);
#elif defined(SPECULARINPUT)
	specularMipMapLevel = max(log2(textureSize(mat_environmentMap, 0).y) - log2(512), 0);
	//specularScale = 0.3;
#else
	specularScale = 0.0;
#endif

	vec3 diffuseEnvPixel = textureLod(mat_environmentMap, g_normal, diffuseMipMapLevel).rgb;
	vec3 reflection = reflect(-g_eye, g_normal);
	vec3 specularEnvPixel = textureLod(mat_environmentMap, reflection, specularMipMapLevel).rgb;

	LightingResult lightingResult = calculateLightingModel(g_normal, vec3(1.0), 1.0, g_normal);
	lightingResult.diffuse *= diffuseEnvPixel;
	lightingResult.specular *= specularEnvPixel * specularScale;

	return lightingResult;
}

LightingResult calculateCustomLighting()
{
	return calculateIBLLighting();
}

#endif