#ifndef _BUMPMAPPING
#define _BUMPMAPPING

#define TBNNORMALS
#define TANGENTSPACE

vec3 normalMap(in vec3 pixelTBNdirection)
{
	vec3 newNormal = normalize(pixelTBNdirection * 2.0 - 1.0) * vec3(1.0, -1.0, 1.0);
	vec3 newNormal2 = normalize(v_tangent) * newNormal.x + normalize(v_bitangent) * newNormal.y + normalize(v_normal) * newNormal.z;

	g_eye = normalize(v_eye);

	return newNormal2;
}

#endif