#version 330
#define M_PI 3.1415926535897932384626433832795
#include "_PointLight.glsl"
#include "_SpotLight.glsl"

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

uniform vec3 mat_diffuse = vec3(0.5);
//uniform vec3 mat_specular = vec3(1.0);
uniform float mat_roughness = 0.5;

in vec3 v_normal;
in vec3 v_eye;
in vec3 v_globalPosition;

out vec4 FragColor;

void calculateWardIsotropic(in vec3 lightVector, in vec3 lightColor, in float brightness, in vec3 normal, in vec3 eye, float roughness, inout vec3 diffuseIntensity, inout vec3 specularIntensity)
{
    vec3 h = normalize( lightVector + eye );
 
    // Generate any useful aliases
    float VdotN = dot( eye, normal );
    float LdotN = dot( lightVector, normal );
    float HdotN = dot( h, normal );
    float roughness_squared = (roughness * roughness) + 0.0001;
    // (Adding a small bias to r_sq stops unexpected
    //  results caused by divide-by-zero)
 
    // Define material properties
    vec3 Ps = vec3( 1.0, 1.0, 1.0 );
 
    // Compute the specular term
    float exp_a;
    /*if( UseLookUpTexture )
    {
        // Map the -1.0..+1.0 dot products to
        // a 0.0..1.0 range suitable for a
        // texture look-up.
        float tc = float2
                    ( 
                        (HdotN + 1.0f) / 2.0f, 
                        0.0f 
                    );
        exp_a = texIsotropicLookup.Sample( DefaultSampler, tc ).r;
    }
    else*/
    //{
        // manually compute the complex term
        exp_a = -pow( tan( acos( HdotN ) ), 2 );
    //}
    float spec_num = exp( exp_a / roughness_squared );
 
    float spec_den = 4.0 * M_PI * roughness_squared;
    spec_den *= sqrt( LdotN * VdotN );
 
    vec3 Specular = Ps * ( spec_num / spec_den );
 
    // Composite the final value:
	diffuseIntensity += max(0, dot( normal, lightVector )) * lightColor * brightness;
	specularIntensity +=  max(vec3(0.0f), Specular) * lightColor * brightness * max(0, dot( normal, lightVector ));
	//color += max(0, dot( normal, lightVector )) * (mat_diffuse + max(vec3(0.0f), Specular) );

    //fragColor = vec4(color, 1.0 );
}

void main()
{
	vec3 normal = normalize( v_normal );
    vec3 lightVector = normalize( u_lightVector );
    vec3 eye = normalize( v_eye );

	vec3 ambient = mat_diffuse * u_lightColor * u_lightAmbient;
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);

	calculateWardIsotropic(lightVector, u_lightColor, u_lightBrightness, normal, eye, mat_roughness, diffuse, specular);

	float brightness;
	for(int i = 0; i < u_pointLights.length(); i++)
	{
		lightVector = calculatePointLightVector(u_pointLights[i], v_globalPosition);
		brightness = calculatePointLightBrightness(u_pointLights[i], v_globalPosition);

		calculateWardIsotropic(lightVector, u_pointLights[i].color, brightness, normal, eye, mat_roughness, diffuse, specular);
	}
	for (int i = 0; i < u_spotLights.length(); i++)
	{
		lightVector = calculateSpotLightVector(u_spotLights[i], v_globalPosition);
		brightness = calculateSpotLightBrightness(u_spotLights[i], v_globalPosition, lightVector);

		calculateWardIsotropic(lightVector, u_spotLights[i].color, brightness, normal, eye, mat_roughness, diffuse, specular);
	}

	diffuse *= mat_diffuse;
	//specular *= mat_specularColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}