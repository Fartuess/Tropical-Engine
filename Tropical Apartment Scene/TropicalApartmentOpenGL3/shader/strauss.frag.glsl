#version 150

#define M_PI 3.1415926535897932384626433832795

struct LightProperties
{
	vec3 direction;
	vec4 ambientColor;
	vec4 diffuseColor;
	vec4 specularColor;
};

struct MaterialProperties
{
	vec4 ambientColor;
	vec4 diffuseColor;
	vec4 specularColor;
	float specularExponent;
};

uniform	LightProperties u_light;
uniform	MaterialProperties u_material;
uniform sampler2D u_texture;
uniform sampler2D u_specular;

in vec3 v_normal;
in vec3 v_eye;
in vec2 v_texCoord;

out vec4 fragColor;

void main()
{
	// Note: All calculations are in camera space.

	vec4 color = u_light.ambientColor *  texture(u_texture, v_texCoord);

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(u_light.direction, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(v_eye);
	
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-u_light.direction, normal);
		
		//original phong shading
		float eDotR = max(dot(eye, reflection), 0.0);

		float smoothness = 0.5;
		float metaliness = 0.5;
		float refractionFactor = 0.1;

		//diffuse without transparency
		color += (1 - pow(smoothness, 3)) * nDotL * (1 - metaliness * smoothness) * u_light.diffuseColor * texture(u_texture, v_texCoord);

		//specular
		float kb = 0.1;
		float kf = 1.12;
		float kg = 1.01;
		float rn = 1;	//temp
		float fresnel = ((1 / pow(x - kf, 2)) - ((1 / pow(kf, 2)))) / ((1 / pow(1 - kf, 2)) - (1 / pow(kf, 2)));
		float geometry = ((1 / pow(x - kg, 2)) - ((1 / pow(kg, 2)))) / ((1 / pow(1 - kg, 2)) - (1 / pow(kg, 2)));;
		float sa = min(1, rn + (rn + kb) * fresnel * pow(geometry, 2));
		vec3 sc = 1 + metaliness * (1 - fresnel) * texture(u_texture, v_texCoord);

		color += -pow(eDotR, (3 / (1 - smoothness))) * sa * sc * u_light.specularColor;
	
		//color += u_light.diffuseColor * texture(u_texture, v_texCoord) * nDotL;
		
		//color += u_light.specularColor * texture(u_specular, v_texCoord) * pow(nDotH, u_material.specularExponent);
		//color += u_light.specularColor * texture(u_specular, v_texCoord) * spec;
	}

	fragColor = color;
}   