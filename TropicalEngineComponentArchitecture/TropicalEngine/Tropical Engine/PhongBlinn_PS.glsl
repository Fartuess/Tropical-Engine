#version 330

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;
uniform vec3 mat_diffuseColor = vec3(0.5);
uniform vec3 mat_specularColor = vec3(1.0);
uniform int mat_specularExponent = 30;

in vec3 v_normal;
in vec3 v_eye;
in vec2 v_texcoord;

out vec4 FragColor;

void main()
{
	vec3 color = u_lightColor * u_lightAmbient * mat_diffuseColor;

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(u_lightVector, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(v_eye);
		
		vec3 reflection = reflect(-u_lightVector, normal);
		
		vec3 H = (u_lightVector + eye)/length(u_lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);
	
		color += u_lightColor * u_lightBrightness * mat_diffuseColor * nDotL;
		
		color += u_lightColor * u_lightBrightness * mat_specularColor * pow(nDotH, mat_specularExponent);
	}

	FragColor = vec4(color, 1.0);
}   