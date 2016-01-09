#ifndef _BUMPTEXTURED
#define _BUMPTEXTURED

#include "Utills/BumpMapping.glsl"

#define TEXTURECOORDINATES

uniform sampler2D mat_color;
uniform sampler2D mat_normal;

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

void processSurface()
{
#ifdef DIFFUSEINPUT
	g_diffuseInput = texture(mat_color, g_texcoord).rgb;
#endif

#ifdef ALBEDOINPUT
	g_albedoInput = texture(mat_color, g_texcoord).rgb;
#endif

	normalMap(texture(mat_normal, g_texcoord).rgb);

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
	g_maskInput = texture(mat_color, g_texcoord).a;
#endif
}

#endif