#version 410

in vec4 a_vertex;
in vec3 a_normal;
in vec3 a_tangent;
in vec3 a_bitangent;
in vec2 a_texcoord;

out vec4 v_vertex_v;
out vec3 v_normal_v;
out vec3 v_tangent_v;
out vec3 v_bitangent_v;
out vec2 v_texcoord_v;

void main()
{
	v_normal_v = a_normal;
	v_tangent_v = a_tangent;
	v_bitangent_v = a_bitangent;
	v_texcoord_v = a_texcoord;
    v_vertex_v = a_vertex;
}