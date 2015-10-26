#version 330
#define M_PI 3.1415926535897932384626433832795
#include "_PointLight.glsl"
#include "_SpotLight.glsl"

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

uniform vec3 mat_diffuseColor = vec3(0.5);
uniform vec3 mat_specularColor = vec3(1.0);
uniform float mat_roughness = 0.5;
uniform float mat_refractiveIndex = 0.15;

in vec3 v_normal;
in vec3 v_eye;
in vec3 v_globalPosition;

out vec4 FragColor;

void calculateCookTorrance(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float roughness, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		vec3 H = (lightVector + eye)/length(lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);

		float alphaDegree = acos(nDotH);
		float beckmanDistribution = exp(-pow(tan(alphaDegree), 2) / pow(roughness, 2)) / (M_PI * pow(roughness, 2) * pow(cos(alphaDegree), 4));
	
		//schlick's approximation of fresnel
		float R = pow((1 - mat_refractiveIndex) / (1 + mat_refractiveIndex), 2); 
		float eDotH = max(dot(eye, H), 0);
		float fresnel = R + (1 - R) * pow(cos(eDotH), 5);
		
		float geometric = min(1.0, min(2.0 * nDotH * dot(normal, eye) / eDotH, (2 * dot(normal, H) * nDotL) / eDotH));
	
		float spec = (fresnel * geometric * beckmanDistribution) / (dot(normal, eye) * M_PI);
	
		diffuseIntensity += lightColor * brightness * nDotL;
		specularIntensity += lightColor * brightness * spec;
	}
}

void main()	//working one
{
	// Note: All calculations are in camera space.
	vec3 lightVector = normalize(u_lightVector);

	vec3 normal = normalize(v_normal);

	vec3 eye = normalize(v_eye);

	vec3 ambient = u_lightColor * u_lightAmbient * mat_diffuseColor;
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);

	calculateCookTorrance(lightVector, u_lightColor, u_lightBrightness, normal, eye, mat_roughness, diffuse, specular);

	float brightness;
	for(int i = 0; i < u_pointLights.length(); i++)
	{
		lightVector = calculatePointLightVector(u_pointLights[i], v_globalPosition);
		brightness = calculatePointLightBrightness(u_pointLights[i], v_globalPosition);

		calculateCookTorrance(lightVector, u_pointLights[i].color, brightness, normal, eye, mat_roughness, diffuse, specular);
	}
	for (int i = 0; i < u_spotLights.length(); i++)
	{
		lightVector = calculateSpotLightVector(u_spotLights[i], v_globalPosition);
		brightness = calculateSpotLightBrightness(u_spotLights[i], v_globalPosition, lightVector);

		calculateCookTorrance(lightVector, u_spotLights[i].color, brightness, normal, eye, mat_roughness, diffuse, specular);
	}

	diffuse *= mat_diffuseColor;
	specular *= mat_specularColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}