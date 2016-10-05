#ifndef _SPOTLIGHT
#define _SPOTLIGHT

#define MAX_SPOT__LIGHTS 2
#define M_PI 3.1415926535897932384626433832795

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float brightness;
	float radius;
	float attenuation;
	float outerAngle;
	float innerAngle;
};
uniform SpotLight u_spotLights[MAX_SPOT__LIGHTS];

vec3 calculateSpotLightVector(SpotLight light, vec3 fragmentPosition)
{
	return normalize(light.position - fragmentPosition);
}

float calculateSpotLightBrightness(SpotLight light, vec3 fragmentPosition, vec3 lightVector)
{
	float LdotLp = dot(light.direction, lightVector);

	if(LdotLp > cos((light.outerAngle / 360.0) * M_PI))
	{
		float lightDistance = distance(light.position, fragmentPosition);
		float lightDistanceFactor = max(1.0 - (lightDistance / light.radius), 0.0);

		float brightness = pow(lightDistanceFactor, light.attenuation) * light.brightness;

		float Xs = cos(light.innerAngle / 360.0 * M_PI);
		float Xe = cos(light.outerAngle / 360.0 * M_PI);
		float spot = 0.0;
		spot = clamp((LdotLp - Xe) / (Xs - Xe), 0.0, 1.0);

		brightness *= spot;

		return brightness;
	}
	else
	{
		return 0.0;
	}
}

#endif