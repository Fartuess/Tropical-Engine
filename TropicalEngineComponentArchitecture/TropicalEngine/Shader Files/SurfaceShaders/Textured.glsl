#ifndef _TEXTURED
#define _TEXTURED

#define TEXTURECOORDINATES

uniform sampler2D mat_colorTexture;

#ifdef SPECULARINPUT
uniform sampler2D mat_specular;
#endif

#ifdef SPECULAREXPONENTINPUT
uniform sampler2D mat_specularExponent;
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
	g_diffuseInput = texture(mat_colorTexture, g_texcoord).rgb;
#endif

#ifdef ALBEDOINPUT
	g_albedoInput = texture(mat_colorTexture, g_texcoord).rgb;
#endif

#ifdef SPECULARINPUT
	g_specularInput = texture(mat_specular, g_texcoord).rgb;
#endif

#ifdef SPECULAREXPONENTINPUT
	g_specularExponentInput = texture(mat_specularExponent, g_texcoord).a;
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
}

#endif