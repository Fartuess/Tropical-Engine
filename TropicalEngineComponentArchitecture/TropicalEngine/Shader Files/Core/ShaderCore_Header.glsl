#ifndef _SHADERCORE_HEADER
#define _SHADERCORE_HEADER

in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec2 v_texcoord;
in vec3 v_eye;
in vec3 v_globalPosition;

vec3 g_color;
vec3 g_normal;
vec3 g_tangent;
vec3 g_bitangent;
vec2 g_texcoord;
vec3 g_eye;

mat3 TBN = mat3(1.0);

layout(location = 0) out vec4 FragColor;

#endif