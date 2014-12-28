#version 330
#include "_PointLight.glsl"

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

uniform vec3 mat_albedo = vec3(0.5);
uniform float mat_roughness = 0.5;
uniform float mat_metaliness = 0.0;
//uniform float mat_refractionFactor;

in vec3 v_normal;
in vec3 v_eye;
in vec3 v_globalPosition;

out vec4 FragColor;

float fresnel(float x)
{
	float kf = 1.12;
	return ((1 / pow(x - kf, 2)) - ((1 / pow(kf, 2)))) / ((1 / pow(1 - kf, 2)) - (1 / pow(kf, 2)));
}

float microfacetShadow(float x)
{
	float kg = 1.01;
	return ((1 / pow(x - kg, 2)) - ((1 / pow(kg, 2)))) / ((1 / pow(1 - kg, 2)) - (1 / pow(kg, 2)));
}

void calculateStrauss(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, vec3 albedo, float roughness, float metalness, inout vec3 color)
{
	vec3 h = reflect( lightVector, normal );
	//vec3 h = (-lightVector + eye)/length(-lightVector + eye);
 
    // Declare any aliases:
    float NdotL   = dot( normal, lightVector );
    float NdotV   = dot( normal, eye );
    float HdotV   = dot( h, eye );
    float fNdotL  = fresnel( NdotL );
    float roughness_cubed = roughness * roughness * roughness;

	float d  = ( 1.0 - metalness * roughness );
	float Rd = ( 1.0 - roughness_cubed );// * ( 1.0f - fTransparency );

	if (NdotL > 0.0)
	{
		// Evaluate the diffuse term
		vec3 diffuse = NdotL * d * Rd * albedo;
 
		// Compute the inputs into the specular term
		float r = ( 1.0 /*- fTransparency*/ ) - Rd;
 
		float j = fNdotL * microfacetShadow( NdotL ) * microfacetShadow( NdotV );
 
		// 'k' is used to provide small off-specular
		// peak for very rough surfaces. Can be changed
		// to suit desired results...
		const float k = 0.1;
		float reflect = min( 1.0, r + j * ( r + k ) );
 
		vec3 vec3_1f = vec3( 1.0, 1.0, 1.0 );
		vec3 Cs = vec3_1f + metalness * (1.0 - fNdotL) * (albedo - vec3_1f);
 
		// Evaluate the specular term
		vec3 specular = Cs * reflect;
		specular *= pow( -HdotV, 3.0 / (1.0 - roughness) );
 
		color  += (max( vec3(0.0), diffuse ) + max( vec3(0.0), specular )) * lightColor * brightness;
		//color += max( vec3(0.0), specular ) * lightColor * u_lightBrightness;
	}
}

void main()
{
    vec3 normal = normalize( v_normal );
    vec3 lightVector = normalize( u_lightVector );
    vec3 eye = normalize( v_eye );

	float roughness_cubed = mat_roughness * mat_roughness * mat_roughness;
	float d  = ( 1.0 - mat_metaliness * mat_roughness );
	float Rd = ( 1.0 - roughness_cubed );// * ( 1.0f - fTransparency );

	vec3 ambient = (d * Rd * mat_albedo) * u_lightColor * u_lightAmbient;
	vec3 color = vec3(0.0);
 
	calculateStrauss(lightVector, u_lightColor, u_lightBrightness, normal, eye, mat_albedo, mat_roughness, mat_metaliness, color);

	float brightness;
	for(int i = 0; i < u_pointLights.length(); i++)
	{
		lightVector = calculatePointLightVector(u_pointLights[i], v_globalPosition);
		brightness = calculatePointLightBrightness(u_pointLights[i], v_globalPosition);

		calculateStrauss(lightVector, u_pointLights[i].color, brightness, normal, eye, mat_albedo, mat_roughness, mat_metaliness, color);
	}

	FragColor = vec4(ambient + color, 1.0);
}