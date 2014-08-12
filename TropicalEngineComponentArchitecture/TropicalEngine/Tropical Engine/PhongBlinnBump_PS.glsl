#version 330

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;
uniform sampler2D mat_diffuseTexture;
uniform sampler2D mat_normalTexture;

in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec3 v_eye;
in vec2 v_texcoord;

out vec4 FragColor;

void main()
{
	vec3 color = u_lightColor * u_lightAmbient * texture(mat_diffuseTexture, v_texcoord);

	vec3 normal = normalize( texture(mat_normalTexture, v_texcoord).xyz * 2.0 - 1.0 );	//change Y to -Y

	mat3 TBN = transpose(mat3(v_tangent, -v_bitangent, v_normal));	//changed Y to -Y here? is it good?

	vec3 lightdir_ts = normalize(TBN * u_lightVector);

	float nDotL = max(dot(lightdir_ts, normal), 0.0);
		
	if (nDotL > 0.0)
	{
		vec3 eye = normalize(TBN * v_eye);
		
		vec3 reflection = reflect(-lightdir_ts, normal);
		
		vec3 H = (lightdir_ts + eye)/length(lightdir_ts + eye);	//maybe just use normalize?
		float nDotH = max(dot(normal, H), 0.0);
	
		color += u_lightColor * u_lightBrightness * texture(mat_diffuseTexture, v_texcoord) * nDotL;
		
		color += u_lightColor * u_lightBrightness * pow(nDotH, 20.0);
	}

	FragColor = vec4(color, 1.0);
}
