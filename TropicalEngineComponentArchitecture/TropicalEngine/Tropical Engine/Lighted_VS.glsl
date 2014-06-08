#version 330

uniform vec2 u_cameraPosition;

in vec4 a_vertex;
in vec3 a_normal;

out vec3 v_normal;

void main()
{
	v_normal = a_normal;
    gl_Position = vec4(0.5 * a_vertex.x + u_cameraPosition.x, 0.5 * a_vertex.y + u_cameraPosition.y, a_vertex.z, 1.0);
}