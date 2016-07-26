#version 410

#ifndef _SIMPLETESSELLATION
#define _SIMPLETESSELLATION

layout(vertices = 3) out;

uniform float u_tessellationOuter = 10.0;
uniform float u_tessellationInner = 10.0;

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

void main()
{
	v_vertex_tcs[gl_InvocationID] = v_vertex[gl_InvocationID];
	v_normal_tcs[gl_InvocationID] = v_normal[gl_InvocationID];
	v_tangent_tcs[gl_InvocationID] = v_tangent[gl_InvocationID];
	v_bitangent_tcs[gl_InvocationID] = v_bitangent[gl_InvocationID];
	v_texcoord_tcs[gl_InvocationID] = v_texcoord[gl_InvocationID];

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = u_tessellationOuter;
		gl_TessLevelOuter[1] = u_tessellationOuter;
		gl_TessLevelOuter[2] = u_tessellationOuter;
		gl_TessLevelInner[0] = u_tessellationInner;
	}
}

#endif