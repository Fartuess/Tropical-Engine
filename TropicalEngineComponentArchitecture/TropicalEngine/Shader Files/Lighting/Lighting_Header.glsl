#ifndef _LIGHTING_HEADER
#define _LIGHTING_HEADER

#include "Lighting/PointLight.glsl"
#include "Lighting/SpotLight.glsl"

#include "Lighting/LightingResult.glsl"

uniform float u_lightAmbient = 0.0;
uniform vec3 u_lightAmbientColor = vec3(1.0, 1.0, 1.0);

//struct DirectionalLight
//{
//	vec3 direction;
//	vec3 color;
//	float brightness;
//};
//uniform DirectionalLight u_directionalLight;

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;

#ifndef AMBIENTCHANNEL
#define AMBIENTCHANNEL
vec3 g_ambientChannel;
#endif

LightingResult g_lightingResult = LightingResult(vec3(0.0), vec3(0.0));

LightingResult calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness, in vec3 eye);

#endif