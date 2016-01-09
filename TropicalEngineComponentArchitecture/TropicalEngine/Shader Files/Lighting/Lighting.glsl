#ifndef _LIGHTING
#define _LIGHTING

#include "Lighting/PointLight.glsl"
#include "Lighting/SpotLight.glsl"

uniform float u_lightAmbient;
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

void calculateLightingModel(in vec3 lightVector, in vec3 lightColor, in float lightBrightness);

// private
void calculateAmbientLighting()
{
	g_ambientChannel = u_lightAmbient * u_lightAmbientColor;
}

// private
void calculateDirectionalLighting()
{
	vec3 lightVector = normalize(TBN * u_lightVector);

	calculateLightingModel(lightVector, u_lightColor, u_lightBrightness);
}

// private
void calculatePointLighting(PointLight light)
{

	vec3 lightVector = normalize(TBN * calculatePointLightVector(light, v_globalPosition));
	float brightness = calculatePointLightBrightness(light, v_globalPosition);

	calculateLightingModel(lightVector, light.color, brightness);
}

// private
void calculateSpotLighting(SpotLight light)
{
	vec3 lightVector = normalize(TBN * calculateSpotLightVector(light, v_globalPosition));
	float brightness = calculateSpotLightBrightness(light, v_globalPosition, lightVector);

	calculateLightingModel(lightVector, light.color, brightness);
}

/**
  * Calculates light for shader. Module requires having some LightingModel module attached.
  */
void calculateLighting()
{
	calculateAmbientLighting();
	calculateDirectionalLighting();
	for (int i = 0; i < u_pointLights.length(); i++)
	{
		calculatePointLighting(u_pointLights[i]);
	}
	for (int i = 0; i < u_spotLights.length(); i++)
	{
		calculateSpotLighting(u_spotLights[i]);
	}
}

#endif