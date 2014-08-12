#version 330

uniform mat4 u_transformationMatrix;	//should be modelview and projection instead of model viewproection
uniform mat3 u_normalMatrix;
uniform mat4 u_cameraMatrix;
uniform mat4 u_projectionMatrix;

in vec4 a_vertex;
in vec3 a_normal;
in vec3 a_tangent;
in vec3 a_bitangent;
in vec2 a_texcoord;

out vec3 v_normal;
out vec3 v_tangent;
out vec3 v_bitangent;
out vec2 v_texcoord;
out vec3 v_eye;	//not sure about it's exact function

void main()
{
	vec4 vertexHelper = u_cameraMatrix * u_transformationMatrix * a_vertex;
	v_eye = -vec3(vertexHelper);
	v_normal = u_normalMatrix * a_normal;
	v_tangent = u_normalMatrix * a_tangent;
	v_bitangent = u_normalMatrix * a_bitangent;
	v_texcoord = a_texcoord;
    gl_Position = u_projectionMatrix * vertexHelper;
}