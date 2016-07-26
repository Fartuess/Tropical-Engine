#version 330

#ifndef _OBJECTSPACEMESH
#define _OBJECTSPACEMESH

in vec4 a_vertex;
in vec3 a_normal;
in vec3 a_tangent;
in vec3 a_bitangent;
in vec2 a_texcoord;

out vec4 v_vertex;
out vec3 v_normal;
out vec3 v_tangent;
out vec3 v_bitangent;
out vec2 v_texcoord;

out vec3 v_eye;

void main()
{
	v_normal = a_normal;
	v_tangent = a_tangent;
	v_bitangent = a_bitangent;
	v_texcoord = a_texcoord;
	v_vertex = a_vertex;

	v_eye = -vec3(a_vertex);

	gl_Position = a_vertex;
}

#endif