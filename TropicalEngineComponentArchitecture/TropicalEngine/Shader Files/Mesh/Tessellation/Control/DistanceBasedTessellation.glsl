#version 410 core

#ifndef _DISTANCEBASEDTESSELLATION
#define _DISTANCEBASEDTESSELLATION

layout(vertices = 3) out;

uniform vec3 u_cameraPosition;
uniform float mat_tesselationMultiplier = 32.0;
uniform mat4 u_transformationMatrix;

in vec4 v_vertex[];
in vec3 v_normal[];
in vec3 v_tangent[];
in vec3 v_bitangent[];
in vec2 v_texcoord[];

out vec4 v_vertex_tcs[];
out vec3 v_normal_tcs[];
out vec3 v_tangent_tcs[];
out vec3 v_bitangent_tcs[];
out vec2 v_texcoord_tcs[];

float GetTessLevel(float Distance0, float Distance1, float length)
{
	float AvgDistance = ((Distance0 + Distance1) / 2.0);
	return max(1.0, ((1.0 * mat_tesselationMultiplier) / ((sqrt(AvgDistance)))) * (length));
}

void main()
{
	v_vertex_tcs[gl_InvocationID] = v_vertex[gl_InvocationID];
	v_normal_tcs[gl_InvocationID] = v_normal[gl_InvocationID];
	v_tangent_tcs[gl_InvocationID] = v_tangent[gl_InvocationID];
	v_bitangent_tcs[gl_InvocationID] = v_bitangent[gl_InvocationID];
	v_texcoord_tcs[gl_InvocationID] = v_texcoord[gl_InvocationID];

	float EyeToVertexDistance0 = length(u_cameraPosition - (u_transformationMatrix * v_vertex[0]).xyz);
	float EyeToVertexDistance1 = length(u_cameraPosition - (u_transformationMatrix * v_vertex[1]).xyz);
	float EyeToVertexDistance2 = length(u_cameraPosition - (u_transformationMatrix * v_vertex[2]).xyz);
	float v0_v1 = length(v_vertex[0].xyz - v_vertex[1].xyz);
	float v1_v2 = length(v_vertex[1].xyz - v_vertex[2].xyz);
	float v2_v0 = length(v_vertex[2].xyz - v_vertex[0].xyz);

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2, v1_v2);
		gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0, v2_v0);
		gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1, v0_v1);
		gl_TessLevelInner[0] = max(gl_TessLevelOuter[2], max(gl_TessLevelOuter[1], gl_TessLevelOuter[0]));
	}
}

#endif