#version 330
#define M_PI 3.1415926535897932384626433832795

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

uniform vec3 mat_diffuse;
//uniform vec3 mat_specular;
uniform float mat_roughness;

in vec3 v_normal;
in vec3 v_eye;

out vec4 fragColor;

void main()
{
	// Make sure the interpolated inputs and
    // constant parameters are normalized
    vec3 n = normalize( v_normal );
    vec3 l = normalize( -u_lightVector );
    vec3 v = normalize( v_eye );
    vec3 h = normalize( l + v );
 
    // Generate any useful aliases
    float VdotN = dot( v, n );
    float LdotN = dot( l, n );
    float HdotN = dot( h, n );
    float roughness_squared = (mat_roughness * mat_roughness) + 0.0001;
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
    fragColor = vec4( dot( n, l ) * (mat_diffuse + Specular ), 1.0 );
}