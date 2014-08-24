#version 330
//#define M_PI 3.1415926535897932384626433832795

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;	//unused, figure out how it should work in strauss.

uniform vec3 mat_albedo;
uniform float mat_roughness;
uniform float mat_metaliness;
uniform float mat_refractionFactor;

in vec3 v_normal;
in vec3 v_eye;
//in vec2 v_texCoord;

out vec4 fragColor;

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

void main()
{
	// Make sure the interpolated inputs and
    // constant parameters are normalized
    vec3 n = normalize( v_normal );
    vec3 l = normalize( -u_lightVector );
    vec3 v = normalize( v_eye );
    vec3 h = reflect( l, n );
 
    // Declare any aliases:
    float NdotL   = dot( n, l );
    float NdotV   = dot( n, v );
    float HdotV   = dot( h, v );
    float fNdotL  = fresnel( NdotL );
    float roughness_cubed = mat_roughness * mat_roughness * mat_roughness;
 
    // Evaluate the diffuse term
    float d  = ( 1.0 - mat_metaliness * mat_roughness );
    float Rd = ( 1.0 - roughness_cubed );// * ( 1.0f - fTransparency );
    vec3 diffuse = NdotL * d * Rd * mat_albedo;
 
    // Compute the inputs into the specular term
    float r = ( 1.0 /*- fTransparency*/ ) - Rd;
 
    float j = fNdotL * microfacetShadow( NdotL ) * microfacetShadow( NdotV );
 
    // 'k' is used to provide small off-specular
    // peak for very rough surfaces. Can be changed
    // to suit desired results...
    const float k = 0.1;
    float reflect = min( 1.0, r + j * ( r + k ) );
 
    vec3 vec3_1f = vec3( 1.0, 1.0, 1.0 );
    vec3 Cs = vec3_1f + mat_metaliness * (1.0 - fNdotL) * (mat_albedo - vec3_1f);
 
    // Evaluate the specular term
    vec3 specular = Cs * reflect;
    specular *= pow( -HdotV, 3.0 / (1.0 - mat_roughness) );
 
    // Composite the final result, ensuring
    // the values are >= 0.0f yields better results. Some
    // combinations of inputs generate negative values which
    // looks wrong when rendered...
    diffuse  = max( 0.0, diffuse );
    specular = max( 0.0, specular );
    fragcolor = vec4( diffuse + specular, 1.0 );
}