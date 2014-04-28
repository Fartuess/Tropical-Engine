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

	vec4 color = u_light.ambientColor /* *  texture(u_texture, v_texCoord)*/;

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(u_light.direction, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(v_eye);
	
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-u_light.direction, normal);
		
		//original phong shading
		//float eDotR = max(dot(eye, reflection), 0.0);

		//Blinn-Phong shading
		vec3 H = (u_light.direction + eye)/length(u_light.direction + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);

		//Cook-Torrance shading
		float roughness = 0.5;	//temporary constant

		float alphaDegree = acos(nDotH);
		//float beckmanDistribution = exp(-pow(tan(alphaDegree), 2) / pow(roughness, 2)) / (M_PI * pow(roughness, 2) * pow(cos(alphaDegree), 4));
		float c2 = 0.1;
		float trobridge_reitzDistribution = pow(pow(c2, 2) / (pow(cos(nDotH), 2) * (pow(c2, 2) - 1) + 1), 2);

		//schlick's approximation of fresnel
		float refractiveIndex = 0.15;
		float R = pow((1 - refractiveIndex) / (1 + refractiveIndex), 2); 
		float eDotH = max(dot(eye, H), 0);
		float fresnel = R + (1 - R) * pow(cos(eDotH), 5);
		
		float geometric = min(1.0, min(2.0 * nDotH * dot(normal, eye) / eDotH, (2 * dot(normal, H) * nDotL) / eDotH));//2.0 * nDotH * dot(normal, eye) / eDotH, (2 * dot(normal, H) * nDotL) / eDotH));

		float spec = (fresnel * geometric * trobridge_reitzDistribution) / (dot(normal, eye) * M_PI);
	
		color += u_light.diffuseColor * /*texture(u_texture, v_texCoord) * */ nDotL * 0.5;
		
		//color += u_light.specularColor * texture(u_specular, v_texCoord) * pow(nDotH, u_material.specularExponent);
		color += u_light.specularColor * /* texture(u_specular, v_texCoord) * */ spec;
	}

	fragColor = color;
}   