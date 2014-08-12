#version 410

layout (vertices = 3) out;

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
    v_normal_tcs[gl_InvocationID]   = v_normal_v[gl_InvocationID];
    v_tangent_tcs[gl_InvocationID] = v_tangent_v[gl_InvocationID];
	v_bitangent_tcs[gl_InvocationID] = v_bitangent_v[gl_InvocationID];
    v_texcoord_tcs[gl_InvocationID]   = v_texcoord_v[gl_InvocationID];

	gl_TessLevelOuter[0] = 7.0;
    gl_TessLevelOuter[1] = 7.0;
    gl_TessLevelOuter[2] = 7.0;
    gl_TessLevelInner[0] = 7.0;
}
