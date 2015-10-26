#version 330
#include "_PointLight.glsl"
#include "_SpotLight.glsl"

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

uniform vec3 mat_diffuseColor = vec3(0.5);
uniform vec3 mat_specularColor = vec3(1.0);
uniform float mat_specularExponent = 20.0;

in vec3 v_normal;
in vec3 v_eye;
in vec3 v_globalPosition;

out vec4 FragColor;

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
	for (int i = 0; i < u_pointLights.length(); i++)
	{
		lightVector = calculatePointLightVector(u_pointLights[i], v_globalPosition);
		brightness = calculatePointLightBrightness(u_pointLights[i], v_globalPosition);

		calculatePhong(lightVector, u_pointLights[i].color, brightness, normal, eye, mat_specularExponent, diffuse, specular);
	}
	for (int i = 0; i < u_spotLights.length(); i++)
	{
		lightVector = calculateSpotLightVector(u_spotLights[i], v_globalPosition);
		brightness = calculateSpotLightBrightness(u_spotLights[i], v_globalPosition, lightVector);

		calculatePhong(lightVector, u_spotLights[i].color, brightness, normal, eye, mat_specularExponent, diffuse, specular);
	}

	diffuse *= mat_diffuseColor;
	specular *= mat_specularColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}
