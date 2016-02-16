#ifndef _IMAGEBASEDLIGHTING
#define _IMAGEBASEDLIGHTING

#include "Lighting/LightingResult.glsl"

#include "Utills/CubeMapping.glsl"
#include "Utills/CubemapReflection.glsl"

#define CUSTOMLIGHTING

uniform sampler2D mat_environmentMap;

LightingResult calculateIBLLighting()
{
	float specularScale = 1.0;

	float diffuseMipMapLevel;
	float specularMipMapLevel;

	diffuseMipMapLevel = max(log2(textureSize(mat_environmentMap, 0).y) - log2(16), 0);

#if defined(ROUGHNESSINPUT)
	specularMipMapLevel = max(log2(textureSize(mat_environmentMap, 0).y) - log2(mix(1024, 16, g_roughnessInput), 0);
	specularScale = 1.0 - g_roughnessInput;
#elif defined(SPECULAREXPONENTINPUT)
	float helperRough = max(min((1.0 / (g_specularExponentInput / 100.0)), 1.0), 0.0);
	specularMipMapLevel = max(log2(textureSize(mat_environmentMap, 0).y) - log2(mix(8, 1024, helperRough)), 0);
	specularScale = max(min((g_specularExponentInput / 100.0), 1.0), 0.0);
#elif defined(SPECULARINPUT)
	specularMipMapLevel = max(log2(textureSize(mat_environmentMap, 0).y) - log2(512), 0);
	specularScale = 0.3;
#else
	specularScale = 0.0;
#endif

	vec3 diffuseEnvPixel = mix(mix(textureLod(mat_environmentMap, cubemap(), diffuseMipMapLevel + 1).rgb, textureLod(mat_environmentMap, cubemap(), diffuseMipMapLevel).rgb, 0.5), textureLod(mat_environmentMap, cubemap(), diffuseMipMapLevel + 2).rgb, 0.5);
	vec3 specularEnvPixel;
	specularEnvPixel = mix(textureLod(mat_environmentMap, cubemapReflection(), specularMipMapLevel + 1).rgb, textureLod(mat_environmentMap, cubemapReflection(), specularMipMapLevel).rgb, 0.5);
	
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