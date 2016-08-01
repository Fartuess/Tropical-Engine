#ifndef _LUTCOLORGRADING
#define _LUTCOLORGRADING

#define TEXTURECOORDINATES

uniform sampler2D mat_color;
uniform sampler2D mat_LUT;

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
#line 43
void processSurface()
{
#ifdef EMISSIVEINPUT
	if (mat_usesEmissive)
	{
		vec3 originalColor = max(min(texture(mat_emissive, g_texcoord).rgb, vec3(1.0, 1.0, 1.0)), vec3(0.0));
		vec3 Lut_texcoord = vec3(
			(originalColor.r * 15),
			15 - (originalColor.g * 15),
			(originalColor.b * 15));
		
		ivec2 LUT_texcoord1 = ivec2(floor(Lut_texcoord.r) + floor(Lut_texcoord.b) * 16, floor(Lut_texcoord.g));
		ivec2 LUT_texcoord2 = ivec2(floor(Lut_texcoord.r) + floor(Lut_texcoord.b) * 16, ceil(Lut_texcoord.g));
		ivec2 LUT_texcoord3 = ivec2(floor(Lut_texcoord.r) + ceil(Lut_texcoord.b) * 16, floor(Lut_texcoord.g));
		ivec2 LUT_texcoord4 = ivec2(floor(Lut_texcoord.r) + ceil(Lut_texcoord.b) * 16, ceil(Lut_texcoord.g));
		ivec2 LUT_texcoord5 = ivec2(ceil(Lut_texcoord.r) + floor(Lut_texcoord.b) * 16, floor(Lut_texcoord.g));
		ivec2 LUT_texcoord6 = ivec2(ceil(Lut_texcoord.r) + floor(Lut_texcoord.b) * 16, ceil(Lut_texcoord.g));
		ivec2 LUT_texcoord7 = ivec2(ceil(Lut_texcoord.r) + ceil(Lut_texcoord.b) * 16, floor(Lut_texcoord.g));
		ivec2 LUT_texcoord8 = ivec2(ceil(Lut_texcoord.r) + ceil(Lut_texcoord.b) * 16, ceil(Lut_texcoord.g));

		vec3 recolored =
			mix
			(
				mix
				(
					mix(texelFetch(mat_LUT, LUT_texcoord1, 0).rgb, texelFetch(mat_LUT, LUT_texcoord2, 0).rgb, fract(Lut_texcoord.g)),
					mix(texelFetch(mat_LUT, LUT_texcoord3, 0).rgb, texelFetch(mat_LUT, LUT_texcoord4, 0).rgb, fract(Lut_texcoord.g)),
					fract(Lut_texcoord.b)
				),
				mix
				(
					mix(texelFetch(mat_LUT, LUT_texcoord5, 0).rgb, texelFetch(mat_LUT, LUT_texcoord6, 0).rgb, fract(Lut_texcoord.g)),
					mix(texelFetch(mat_LUT, LUT_texcoord7, 0).rgb, texelFetch(mat_LUT, LUT_texcoord8, 0).rgb, fract(Lut_texcoord.g)),
					fract(Lut_texcoord.b)
				),
				fract(Lut_texcoord.r)
			);
		g_emissiveInput = recolored;
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