#version 330
#include "_PointLight.glsl"
#include "_SpotLight.glsl"

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;
uniform sampler2D mat_diffuseTexture;
uniform sampler2D mat_normalTexture;
uniform vec3 mat_specularColor = vec3(1.0f);	///TODO: figure out how to make it into a texture with default value
uniform float mat_specularExponent = 30.0;

in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec3 v_eye;
in vec2 v_texcoord;
in vec3 v_globalPosition;

out vec4 FragColor;

void calculateBlinn(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float specularExponent, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
	float nDotL = max(dot(lightVector, normal), 0.0);
	if (nDotL > 0.0)
	{
		vec3 reflection = reflect(-lightVector, normal);
		vec3 H = (lightVector + eye)/length(lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);
	
		diffuseIntensity += lightColor * brightness * nDotL;
		specularIntensity += lightColor * brightness * pow(nDotH, specularExponent);
	}
}

void main()
{
	vec3 ambient = u_lightColor * u_lightAmbient * texture(mat_diffuseTexture, v_texcoord).rgb;
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);

	vec3 normal = normalize( texture(mat_normalTexture, v_texcoord).xyz * 2.0 - 1.0 );

	mat3 TBN = transpose(mat3(v_tangent, v_bitangent, v_normal));

	vec3 lightVector = normalize(TBN * u_lightVector);

	vec3 eye = normalize(TBN * v_eye);

	calculateBlinn(lightVector, u_lightColor, u_lightBrightness, normal, eye, mat_specularExponent, diffuse, specular);

	float brightness;
	for(int i = 0; i < u_pointLights.length(); i++)
	{
		lightVector = normalize(TBN * calculatePointLightVector(u_pointLights[i], v_globalPosition));
		brightness = calculatePointLightBrightness(u_pointLights[i], v_globalPosition);

		calculateBlinn(lightVector, u_pointLights[i].color, brightness, normal, eye, mat_specularExponent, diffuse, specular);
	}
	for (int i = 0; i < u_spotLights.length(); i++)
	{
		lightVector = calculateSpotLightVector(u_spotLights[i], v_globalPosition);
		brightness = calculateSpotLightBrightness(u_spotLights[i], v_globalPosition, lightVector);

		calculateBlinn(lightVector, u_spotLights[i].color, brightness, normal, eye, mat_specularExponent, diffuse, specular);
	}

	diffuse *= texture(mat_diffuseTexture, v_texcoord).rgb;
	specular *= mat_specularColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}
