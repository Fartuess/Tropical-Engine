#ifndef _TEXTURED
#define _TEXTURED

#define TEXTURECOORDINATES

uniform sampler2D mat_color;

#ifdef SPECULARINPUT
uniform bool mat_specularUsesTexture = false;
uniform vec3 mat_specular = vec3(1.0);
uniform sampler2D mat_specularTexture;
#endif

#ifdef SPECULAREXPONENTINPUT
uniform float mat_specularExponent = 30.0;
#endif

#ifdef ROUGHNESSINPUT
uniform sampler2D mat_roughness;
#endif

#ifdef ANISOROUGHNESSINPUT
uniform sampler2D mat_roughness;
#endif

#ifdef METALNESSINPUT
uniform sampler2D mat_metalness;
#endif

#ifdef MASKINPUT
uniform bool mat_maskSeparateTexture = false;
uniform sampler2D mat_mask;
#endif

#ifndef EMISSIVEINPUT
#define EMISSIVEINPUT
uniform sampler2D mat_emissive;
uniform bool mat_usesEmissive = false;
vec3 g_emissiveInput = vec3(0.0);
#endif

void processSurface()
{
#ifdef EMISSIVEINPUT
	if (mat_usesEmissive)
	{
		g_emissiveInput = texture(mat_emissive, g_texcoord).rgb;
	}
#endif

#ifdef DIFFUSEINPUT
	g_diffuseInput = texture(mat_color, g_texcoord).rgb;
#endif

#ifdef ALBEDOINPUT
	g_albedoInput = texture(mat_color, g_texcoord).rgb;
#endif

#ifdef SPECULARINPUT
	if (mat_specularUsesTexture)
	{
		g_specularInput = texture(mat_specularTexture, g_texcoord).rgb;
	}
	else
	{
		g_specularInput = mat_specular;
	}
#endif

#ifdef SPECULAREXPONENTINPUT
	g_specularExponentInput = mat_specularExponent;
#endif

#ifdef ROUGHNESSINPUT
	g_roughnessInput = texture(mat_roughness, g_texcoord).a;
#endif

#ifdef ANISOROUGHNESSINPUT
	g_anisoRoughnessInput = texture(mat_roughness, g_texcoord).rg;
#endif

#ifdef METALNESSINPUT
	g_metalnessInput = texture(mat_metalness, g_texcoord).a;
#endif

#ifdef MASKINPUT
	if (mat_maskSeparateTexture)
	{
		g_maskInput = texture(mat_mask, g_texcoord).r;
	}
	else
	{
		g_maskInput = texture(mat_color, g_texcoord).a;
	}
#endif
}

#endif