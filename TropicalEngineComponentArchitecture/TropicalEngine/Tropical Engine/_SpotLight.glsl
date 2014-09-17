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
}
uniform SpotLight u_spotLights[MAX_SPOT__LIGHTS];

vec3 calculatSpotLightVector(SpotLight light, vec3 fragmentPosition)
{
	return normalize(light.position - fragmentPosition);
}

float calculateBrightness(SpotLight light, vec3 fragmentPosition, vec3 lightVector)
{
	float LdotLp = dot(light.direction, lightVector);
	if(LdotLp > cos(light.outerAngle / 90.0 * M_PI))
	{
		float lightDistance = distance(light.position, fragmentPosition);
		float lightDistanceFactor = max(1.0 - (lightDistance / light.radius), 0.0);

		float brightness = pow(lightDistanceFactor, light.attenuation) * light.brightness;
		///TODO: Add inner angle support
		brightness *= max((LdotLp * (180.0 / light.outerAngle)), 0.0);
	}
	else
	{
		return 0.0;
	}
}