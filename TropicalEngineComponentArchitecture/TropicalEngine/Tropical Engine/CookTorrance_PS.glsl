#version 330
#define M_PI 3.1415926535897932384626433832795

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

out vec4 fragColor;

void main()	//working one
{
	// Note: All calculations are in camera space.
	vec3 lightVector = normalize(u_lightVector);

	vec3 color = u_lightColor * u_lightAmbient * mat_diffuseColor;

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(lightVector, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(v_eye);
	
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-lightVector, normal);
		
		//original phong shading
		//float eDotR = max(dot(eye, reflection), 0.0);
	
		//Blinn-Phong shading
		vec3 H = (lightVector + eye)/length(lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);
	
		//Cook-Torrance shading
		//float roughness = 0.5;	//temporary constant
	
		float alphaDegree = acos(nDotH);
		float beckmanDistribution = exp(-pow(tan(alphaDegree), 2) / pow(mat_roughness, 2)) / (M_PI * pow(mat_roughness, 2) * pow(cos(alphaDegree), 4));
	
		//schlick's approximation of fresnel
		//float refractiveIndex = 0.15;
		float R = pow((1 - mat_refractiveIndex) / (1 + mat_refractiveIndex), 2); 
		float eDotH = max(dot(eye, H), 0);
		float fresnel = R + (1 - R) * pow(cos(eDotH), 5);
		
		float geometric = min(1.0, min(2.0 * nDotH * dot(normal, eye) / eDotH, (2 * dot(normal, H) * nDotL) / eDotH));//2.0 * nDotH * dot(normal, eye) / eDotH, (2 * dot(normal, H) * nDotL) / eDotH));
	
		float spec = (fresnel * geometric * beckmanDistribution) / (dot(normal, eye) * M_PI);
	
		color += u_lightColor * u_lightBrightness * mat_diffuseColor * nDotL;
		
		//color += u_light.specularColor * texture(u_specular, v_texCoord) * pow(nDotH, u_material.specularExponent);
		color += u_lightColor * u_lightBrightness * mat_specularColor * spec;
	}

	fragColor = vec4(color, 1.0);
}   