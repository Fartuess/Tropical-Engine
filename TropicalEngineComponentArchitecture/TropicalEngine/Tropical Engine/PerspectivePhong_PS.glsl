#version 330

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

in vec3 v_normal;
in vec3 v_eye;

out vec4 FragColor;

void main()
{
	vec3 baseColor = vec3(0.8, 0.8, 0.8);

	vec3 lightVector = normalize(u_lightVector);

	vec3 color = u_lightColor * u_lightAmbient * baseColor;

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(lightVector, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(v_eye);
		
		//vec3 eye = vec3(0.0, 0.0, -1.0);
		// Incident vector is opposite light direction vector.
		vec3 reflection = reflect(-lightVector, normal);
		
		float eDotR = max(dot(eye, reflection), 0.0);
	
		color += u_lightColor * u_lightBrightness * baseColor * nDotL;
		
		color += u_lightColor * u_lightBrightness * pow(eDotR, 20);
	}

	FragColor = vec4(color, 1.0);
}
