#version 150

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

in vec3 v_normal;
in vec3 v_eye;
in vec2 v_texCoord;

out vec4 fragColor;

void main()
{
	// Note: All calculations are in camera space.

	vec4 color = u_light.ambientColor *  texture(u_texture, 2*v_texCoord);

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(u_light.direction, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(v_eye);
	
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-u_light.direction, normal);
		
		float eDotR = max(dot(eye, reflection), 0.0);
	
		color += u_light.diffuseColor * texture(u_texture, 2*v_texCoord) * nDotL;
		
		color += u_light.specularColor * u_material.specularColor * pow(eDotR, u_material.specularExponent);
	}

	fragColor = color;
}   