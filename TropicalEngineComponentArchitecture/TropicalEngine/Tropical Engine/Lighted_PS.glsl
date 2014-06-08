#version 330

in vec3 v_normal;

out vec4 FragColor;

void main()
{
	vec3 baseColor = vec3(1.0, 0.0, 0.0);

	vec3 lightVector = normalize(vec3(-1.0, 0.0, 0.0));

	vec3 color = 0.1 * baseColor;

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(lightVector, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		//vec3 eye = normalize(v_eye);
	
		// Incident vector is opposite light direction vector.
		//vec3 reflection = reflect(-u_light.direction, normal);
		
		//float eDotR = max(dot(eye, reflection), 0.0);
	
		color += 0.8 * vec3(1.0, 0.0, 0.0) * nDotL;
		
		//color += u_light.specularColor * u_material.specularColor * pow(eDotR, u_material.specularExponent);
	}

	//FragColor = vec4(color, 1.0);

    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
