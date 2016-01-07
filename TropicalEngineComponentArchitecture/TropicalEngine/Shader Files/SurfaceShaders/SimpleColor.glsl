#ifndef _SIMPLECOLOR
#define _SIMPLECOLOR

uniform vec3 mat_color = vec3(0.5);

#ifdef SPECULARINPUT
uniform vec3 mat_specular = vec3(0.5);
#endif

#ifdef SPECULAREXPONENTINPUT
uniform float mat_specularExponent = 20.0;
#endif

#ifdef ROUGHNESSINPUT
uniform float mat_roughness = 0.5;
#endif

#ifdef ANISOROUGHNESSINPUT
uniform vec2 mat_roughness = vec2(0.5);
#endif

#ifdef METALNESSINPUT
uniform float mat_metalness = 0.0;
#endif

#ifdef REFRACITVEINDEXINPUT
uniform float mat_refractiveIndex = 0.15;
#endif

#ifndef EMISSIVEINPUT
#define EMISSIVEINPUT
uniform vec3 mat_emissive = vec3(0.0);
vec3 g_emissiveInput = vec3(0.0);
#endif

void processSurface()
{
#ifdef DIFFUSEINPUT
	g_diffuseInput = mat_color;
#endif

#ifdef ALBEDOINPUT
	g_albedoInput = mat_color;
#endif

#ifdef SPECULARINPUT
	g_specularInput = mat_specular;
#endif

#ifdef SPECULAREXPONENTINPUT
	g_specularExponentInput = mat_specularExponent;
#endif

#ifdef ROUGHNESSINPUT
	g_roughnessInput = mat_roughness;
#endif

#ifdef ANISOROUGHNESSINPUT
	 g_anisoRoughnessInput = mat_roughness;
#endif

#ifdef METALNESSINPUT
	g_metalnessInput = mat_metalness;
#endif

#ifdef REFRACITVEINDEXINPUT
	g_refractiveIndexInput =  mat_refractiveIndex;
#endif

#ifdef EMISSIVEINPUT
	g_emissiveInput = mat_emissive;
#endif
}

#endif