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
//uniform sampler2D u_texture;
//uniform sampler2D u_specular;
//uniform sampler2D u_normalMap;

in vec3 v_normal;
in vec3 v_eye;
in vec2 v_texCoord;
in vec3 v_tangent;
in vec3 v_bitangent;

out vec4 fragColor;

void main()
{
	// Note: All calculations are in camera space.

	vec4 color = u_light.ambientColor;// *  texture(u_texture, v_texCoord);

	// Convert the color information to a normal.
	//vec3 normal = normalize( texture(u_normalMap, v_texCoord).xyz * 2.0 - 1.0 );

	//mat3 TBN = transpose(mat3(v_tangent, v_bitangent, v_normal));

	//vec3 lightdir_ts = normalize(TBN * u_light.direction);
	vec3 lightdir_ts = normalize(u_light.direction);

	vec3 normal = normalize(v_normal);
	float nDotL = max(dot(lightdir_ts, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		//vec3 eye = normalize(TBN * v_eye);
		vec3 eye = normalize(v_eye);
	
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-lightdir_ts, normal);
		
		//original phong shading
		//float eDotR = max(dot(eye, reflection), 0.0);

		//Blinn-Phong shading
		vec3 H = (lightdir_ts + eye)/length(lightdir_ts + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);
	
		//color += u_light.diffuseColor * texture(u_texture, v_texCoord) * nDotL;
		//color += u_light.specularColor * texture(u_specular, v_texCoord) * pow(nDotH, u_material.specularExponent);

		color += u_light.diffuseColor * nDotL;
		color += u_light.specularColor * pow(nDotH, u_material.specularExponent);
	}

	fragColor = color;
}   