#version 330

uniform mat4 u_transformationMatrix;
uniform mat3 u_normalMatrix;
uniform mat4 u_cameraMatrix;

in vec4 a_vertex;
in vec3 a_normal;
in vec2 a_texcoord;

out vec3 v_normal;
out vec2 v_texcoord;
out vec3 v_eye;	//not sure about it's exact function

void main()
{
	vec4 vertexHelper = u_transformationMatrix * a_vertex;
	v_eye = -vec3(a_vertex);
	v_normal = u_normalMatrix * a_normal;
	v_texcoord = a_texcoord;
    gl_Position = u_cameraMatrix * vertexHelper;
}