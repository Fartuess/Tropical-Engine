#ifndef _SIMPLETESSELLATION
#define _SIMPLETESSELLATION

#version 410

layout(vertices = 3) out;

uniform float u_tessellationOuter = 10.0;
uniform float u_tessellationInner = 10.0;

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

void main()
{
	v_vertex_tcs[gl_InvocationID] = v_vertex_v[gl_InvocationID];
	v_normal_tcs[gl_InvocationID] = v_normal_v[gl_InvocationID];
	v_tangent_tcs[gl_InvocationID] = v_tangent_v[gl_InvocationID];
	v_bitangent_tcs[gl_InvocationID] = v_bitangent_v[gl_InvocationID];
	v_texcoord_tcs[gl_InvocationID] = v_texcoord_v[gl_InvocationID];

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = u_tessellationOuter;
		gl_TessLevelOuter[1] = u_tessellationOuter;
		gl_TessLevelOuter[2] = u_tessellationOuter;
		gl_TessLevelInner[0] = u_tessellationInner;
	}
}

#endif