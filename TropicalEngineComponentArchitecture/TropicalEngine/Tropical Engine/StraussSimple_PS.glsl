#version 330
//#define M_PI 3.1415926535897932384626433832795

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

uniform vec3 mat_albedo;
uniform float mat_roughness;
uniform float mat_metaliness;
uniform float mat_refractionFactor;

in vec3 v_normal;
in vec3 v_eye;
in vec2 v_texCoord;

out vec4 fragColor;

void main()	//wasn't working properly in previous project
{
	// Note: All calculations are in camera space.

	vec4 color = u_lightAmbient * mat_albedo;

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(u_lightVector, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(v_eye);
	
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-u_lightVector, normal);
		
		//original phong shading
		float eDotR = max(dot(eye, reflection), 0.0);

		//float smoothness = 0.5;
		//float metaliness = 0.5;
		float refractionFactor = 0.1;	//is it needed since we're not using translucency?

		//diffuse without transparency
		color += (1 - pow(mat_roughness, 3)) * nDotL * (1 - mat_metaliness * mat_roughness) * u_lightColor * mat_albedo;

		//specular
		float kb = 0.1;
		float kf = 1.12;
		float kg = 1.01;
		float rn = 1;	//temp
		float fresnel = ((1 / pow(x - kf, 2)) - ((1 / pow(kf, 2)))) / ((1 / pow(1 - kf, 2)) - (1 / pow(kf, 2)));
		float geometry = ((1 / pow(x - kg, 2)) - ((1 / pow(kg, 2)))) / ((1 / pow(1 - kg, 2)) - (1 / pow(kg, 2)));
		float sa = min(1, rn + (rn + kb) * fresnel * pow(geometry, 2));
		vec3 sc = 1 + mat_metaliness * (1 - fresnel) * mat_albedo;

		color += -pow(eDotR, (3 / (1 - mat_roughness))) * sa * sc * u_lightColor;
	
		//color += u_light.diffuseColor * texture(u_texture, v_texCoord) * nDotL;
		
		//color += u_light.specularColor * texture(u_specular, v_texCoord) * pow(nDotH, u_material.specularExponent);
		//color += u_light.specularColor * texture(u_specular, v_texCoord) * spec;
	}

	fragColor = color;
}   