#version 150

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;
uniform mat3 u_normalMatrix;

in vec4 a_vertex;
in vec3 a_normal;
in vec2 a_texCoord;

in vec3 a_tangent;
in vec3 a_bitangent;

out vec3 v_normal;
out vec3 v_eye;
out vec2 v_texCoord;

out vec3 v_tangent;
out vec3 v_bitangent;

void main()
{
	vec4 vertex = u_modelViewMatrix * a_vertex;

	v_eye = -vec3(vertex);

	v_normal = u_normalMatrix * a_normal;

	v_texCoord = a_texCoord;
		
	gl_Position = u_projectionMatrix * vertex;

	v_tangent = u_normalMatrix * a_tangent;
	v_bitangent = u_normalMatrix * a_bitangent;
}    