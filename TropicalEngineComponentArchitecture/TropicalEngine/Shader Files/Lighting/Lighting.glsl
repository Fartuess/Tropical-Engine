#ifndef _LIGHTING
#define _LIGHTING

#include "Lighting/PointLight.glsl"
#include "Lighting/SpotLight.glsl"

uniform float u_lightAmbient;
uniform vec3 u_lightAmbientColor = vec3(1.0, 1.0, 1.0);

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float brightness;
};
uniform u_directionalLight;

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
void calculateDirecationalLighting()
{
	vec3 lightVector = normalize(u_directionalLight.direction);
#ifdef TBNNORMALS
	lightVector = normalize(TBN * lightVector);
#endif
	calculateLightingModel(lightVector, u_directionalLight.color, u_directionalLight.brightness);
}

// private
void calculatePointLighting(PointLight light)
{
	vec3 lightVector = calculatePointLightVector(light, v_globalPosition);
#ifdef TBNNORMALS
	lightVector = normalize(TBN * lightVector);
#endif
	float brightness = calculatePointLightBrightness(light, v_globalPosition);

	calculateLightingModel(lightVector, light.color, brightness);
}

// private
void calculateSpotLighting(SpotLight light)
{
	vec3 lightVector = calculateSpotLightVector(light, v_globalPosition);
#ifdef TBNNORMALS
	lightVector = normalize(TBN * lightVector);
#endif
	float brightness = calculateSpotLightBrightness(light, v_globalPosition, lightVector);

	calculateLightingModel(lightVector, light.color, brightness);
}

/**
  * Calculates light for shader. Module requires having some LightingModel module attached.
  */
void calculateLighting()
{
	calculateAmbientLighting();
	calculateDirecationalLighting();
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