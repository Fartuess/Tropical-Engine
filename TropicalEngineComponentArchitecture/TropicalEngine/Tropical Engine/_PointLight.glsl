#define MAX_POINT_LIGHTS 2
struct PointLight
{
	vec3 position;
	vec3 color;
	float brightness;
	float radius;
	float attenuation;
};
uniform PointLight u_pointLights[MAX_POINT_LIGHTS];

vec3 calculatePointLightVector(PointLight light, vec3 fragmentPosition)
{
	return normalize(light.position - fragmentPosition);
}

float calculatePointLightBrightness(PointLight light, vec3 fragmentPosition)
{
	float lightDistance = distance(light.position, fragmentPosition);
	float lightDistanceFactor = max(1.0 - (lightDistance / light.radius), 0.0);

	return pow(lightDistanceFactor, light.attenuation) * light.brightness;
}