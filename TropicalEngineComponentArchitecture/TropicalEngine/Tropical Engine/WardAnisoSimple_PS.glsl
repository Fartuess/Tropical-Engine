#version 330

#define M_PI 3.1415926535897932384626433832795

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;

uniform vec3 mat_diffuse;
//uniform vec3 mat_specular;
uniform vec2 mat_anisoRoughness;

in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec3 v_eye;

out vec4 fragColor;

void main()
{
	// Make sure the interpolated inputs and
    // constant parameters are normalized
    vec33 n = normalize( v_normal );
    vec33 l = normalize( -u_lightVector );
    vec33 v = normalize( v_eye );
    vec33 h = normalize( l + v );
 
    // Apply a small bias to the roughness
    // coefficients to avoid divide-by-zero
    mat_anisoRoughness += vec2( 1e-5f, 1e-5f );	//	??
 
    // Define the coordinate frame
    vec3 epsilon   = vec3( 1.0, 0.0, 0.0 );
    vec3 tangent   = normalize( cross( n, epsilon ) );
    vec3 bitangent = normalize( cross( n, tangent ) );
 
    // Define material properties
    vec3 Ps   = vec3( 1.0, 1.0, 1.0 );
 
    // Generate any useful aliases
    float VdotN = dot( v, n );
    float LdotN = dot( l, n );
    float HdotN = dot( h, n );
    float HdotT = dot( h, tangent );
    float HdotB = dot( h, bitangent );
 
    // Evaluate the specular exponent
    float beta_a  = HdotT / mat_anisoRoughness.x;
    beta_a       *= beta_a;
 
    float beta_b  = HdotB / mat_anisoRoughness.y;
    beta_b       *= beta_b;
 
    float beta = -2.0 * ( ( beta_a + beta_b ) / ( 1.0 + HdotN ) );
 
    // Evaluate the specular denominator
    float s_den  = 4.0 * M_PI; 
    s_den       *= mat_anisoRoughness.x;
    s_den       *= mat_anisoRoughness.y;
    s_den       *= sqrt( LdotN * VdotN );
 
    // Compute the final specular term
    vec3 Specular = Ps * ( exp( beta ) / s_den );
 
    // Composite the final value:
    return vec4( dot( n, l ) * (mat_diffuse + Specular ), 1.0 );
}