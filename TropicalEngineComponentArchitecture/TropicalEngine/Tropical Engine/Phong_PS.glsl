#version 330

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

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

uniform vec3 mat_diffuseColor = vec3(0.5);
uniform vec3 mat_specularColor = vec3(1.0);
uniform float mat_specularExponent = 20.0;

in vec3 v_normal;
in vec3 v_eye;
in vec3 v_globalPosition;

out vec4 FragColor;

vec3 calculatePointLightVector(PointLight light, vec3 fragmentPosition)
{
	return normalize(light.position - fragmentPosition);
}

float calculatePointLightBrightness(PointLight light, vec3 fragmentPosition)
{
	float lightDistance = distance(light.position, fragmentPosition);
	float lightDistanceFactor = max(1.0 - (lightDistance / light.radius), 0.0);

	return pow(lightDistanceFactor, light.attenuation) * light.brightness;
	//return lightDistanceFactor;
}

void calculatePhong(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float specularExponent, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{	
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-lightVector, normal);
		float eDotR = max(dot(eye, reflection), 0.0);
	
		diffuseIntensity += lightColor * brightness *  nDotL;
		specularIntensity += lightColor * brightness * pow(eDotR, specularExponent);
	}
}

void main()
{

	vec3 lightVector = normalize(u_lightVector);

	vec3 normal = normalize(v_normal);

	vec3 eye = normalize(v_eye);

	vec3 ambient = u_lightColor * u_lightAmbient * mat_diffuseColor;
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);

	calculatePhong(lightVector, u_lightColor, u_lightBrightness, normal, eye, mat_specularExponent, diffuse, specular);

	float brightness;
	for(int i = 0; i < u_pointLights.length(); i++)
	{
		lightVector = calculatePointLightVector(u_pointLights[i], v_globalPosition);
		brightness = calculatePointLightBrightness(u_pointLights[i], v_globalPosition);

		calculatePhong(lightVector, u_pointLights[i].color, brightness, normal, eye, mat_specularExponent, diffuse, specular);
	}

	diffuse *= mat_diffuseColor;
	specular *= mat_specularColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}
