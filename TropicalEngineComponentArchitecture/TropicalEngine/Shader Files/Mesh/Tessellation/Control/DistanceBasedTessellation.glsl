#ifndef _DISTANCEBASEDTESSELLATION
#define _DISTANCEBASEDTESSELLATION

#version 410 core

layout(vertices = 3) out;

uniform vec3 u_cameraPosition;
uniform float mat_tesselationMultiplier = 32.0;
uniform mat4 u_transformationMatrix;

in vec4 v_vertex_v[];
in vec3 v_normal_v[];
in vec3 v_tangent_v[];
in vec3 v_bitangent_v[];
in vec2 v_texcoord_v[];

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
	v_vertex_tcs[gl_InvocationID] = v_vertex_v[gl_InvocationID];
	v_normal_tcs[gl_InvocationID] = v_normal_v[gl_InvocationID];
	v_tangent_tcs[gl_InvocationID] = v_tangent_v[gl_InvocationID];
	v_bitangent_tcs[gl_InvocationID] = v_bitangent_v[gl_InvocationID];
	v_texcoord_tcs[gl_InvocationID] = v_texcoord_v[gl_InvocationID];

	float EyeToVertexDistance0 = length(u_cameraPosition - (u_transformationMatrix * v_vertex_v[0]).xyz);
	float EyeToVertexDistance1 = length(u_cameraPosition - (u_transformationMatrix * v_vertex_v[1]).xyz);
	float EyeToVertexDistance2 = length(u_cameraPosition - (u_transformationMatrix * v_vertex_v[2]).xyz);
	float v0_v1 = length(v_vertex_v[0].xyz - v_vertex_v[1].xyz);
	float v1_v2 = length(v_vertex_v[1].xyz - v_vertex_v[2].xyz);
	float v2_v0 = length(v_vertex_v[2].xyz - v_vertex_v[0].xyz);

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2, v1_v2);
		gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0, v2_v0);
		gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1, v0_v1);
		gl_TessLevelInner[0] = max(gl_TessLevelOuter[2], max(gl_TessLevelOuter[1], gl_TessLevelOuter[0]));
	}
}

#endif