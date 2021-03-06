#version 330

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;
uniform sampler2D mat_diffuseTexture;

in vec3 v_normal;
in vec3 v_eye;
in vec2 v_texcoord;

out vec4 FragColor;

void main()
{
	vec3 color = u_lightColor * u_lightAmbient * texture(mat_diffuseTexture, v_texcoord).rgb;

	vec3 normal = normalize(v_normal);

	float nDotL = max(dot(u_lightVector, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(v_eye);
		
		vec3 reflection = reflect(-u_lightVector, normal);
		
		vec3 H = (u_lightVector + eye)/length(u_lightVector + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);
	
		color += u_lightColor * u_lightBrightness * texture(mat_diffuseTexture, v_texcoord).rgb * nDotL;
		
		color += u_lightColor * u_lightBrightness * pow(nDotH, 20.0);
	}

	FragColor = vec4(color, 1.0);
}   