#ifndef _BUMPMAPPING
#define _BUMPMAPPING

#define TBNNORMALS
#define TANGENTSPACE

void normalMap(in vec3 pixelTBNdirection)
{
	g_normal = normalize(pixelTBNdirection * 2.0 - 1.0);

	// TODO: Change g_tangent and g_bitangent for shaders which uses them (like anisotropic lighting models)

	TBN = transpose(mat3(v_tangent, v_bitangent, v_normal));

	g_eye = normalize(TBN * v_eye);
}

#endif