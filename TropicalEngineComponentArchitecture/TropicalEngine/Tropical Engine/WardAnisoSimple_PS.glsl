#version 330
#define M_PI 3.1415926535897932384626433832795
#include "_PointLight.glsl"

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

uniform vec3 mat_diffuse = vec3(0.5);
//uniform vec3 mat_specular;
uniform vec2 mat_anisoRoughness = vec2(0.5);

in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec3 v_eye;
in vec3 v_globalPosition;

out vec4 FragColor;

void calculateWardAnisotropic(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 tangent, in vec3 bitangent, in vec3 eye, in vec2 anisoRoughness, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
	vec3 h = normalize( lightVector + eye );
    // Generate any useful aliases
    float VdotN = dot( eye, normal );
    float LdotN = dot( lightVector, normal );
    float HdotN = dot( h, normal );
    float HdotT = dot( h, tangent );
    float HdotB = dot( h, bitangent );
 
    // Evaluate the specular exponent
    float beta_a  = HdotT / anisoRoughness.x;
    beta_a       *= beta_a;
 
    float beta_b  = HdotB / anisoRoughness.y;
    beta_b       *= beta_b;
 
    float beta = -2.0 * ( ( beta_a + beta_b ) / ( 1.0 + HdotN ) );
 
    // Evaluate the specular denominator
    float s_den  = 4.0 * M_PI; 
    s_den       *= anisoRoughness.x;
    s_den       *= anisoRoughness.y;
    s_den       *= sqrt( LdotN * VdotN );
 
    // Compute the final specular term
    vec3 Specular = /*Ps * */ ( exp( beta ) / s_den );
 
    // Composite the final value:

	diffuseIntensity += max(0, dot( normal, lightVector )) * lightColor * brightness;
	specularIntensity +=  max(vec3(0.0f), Specular) * lightColor * brightness * max(0, dot( normal, lightVector ));

	//diffuseIntensity +=
	//specularIntensity +=
	//color += max(0,dot( normal, lightVector )) * (mat_diffuse + max(vec3(0.0), Specular) );
}

void main()
{
	vec3 ambient = mat_diffuse * u_lightColor * u_lightAmbient;
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);
	// Make sure the interpolated inputs and
    // constant parameters are normalized
    vec3 normal = normalize(v_normal);
	vec3 tangent = normalize(v_tangent);
	vec3 bitangent = normalize(v_bitangent);
    vec3 lightVector = normalize( u_lightVector );
    vec3 eye = normalize( v_eye );
 
    // Apply a small bias to the roughness
    // coefficients to avoid divide-by-zero
    vec2 anisoRoughness = mat_anisoRoughness + vec2( 1e-5f, 1e-5f );	//	??
 
    // Define the coordinate frame
    //vec3 epsilon   = vec3( 1.0, 0.0, 0.0 );
    //vec3 tangent   = normalize( cross( normal, epsilon ) );
    //vec3 bitangent = normalize( cross( normal, tangent ) );
 
    // Define material properties
    //vec3 Ps   = vec3( 1.0, 1.0, 1.0 );

	calculateWardAnisotropic(lightVector, u_lightColor, u_lightBrightness, normal, tangent, bitangent, eye, anisoRoughness, diffuse, specular);

	float brightness;
	for(int i = 0; i < u_pointLights.length(); i++)
	{
		lightVector = calculatePointLightVector(u_pointLights[i], v_globalPosition);
		brightness = calculatePointLightBrightness(u_pointLights[i], v_globalPosition);

		calculateWardAnisotropic(lightVector, u_pointLights[i].color, brightness, normal, tangent, bitangent, eye, anisoRoughness, diffuse, specular);
	}

	diffuse *= mat_diffuse;
	//specular *= mat_specularColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}