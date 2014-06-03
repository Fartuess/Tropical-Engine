#version 330

uniform vec2 u_cameraPosition;

layout (location = 0) in vec3 Position;

void main()
{
    gl_Position = vec4(0.5 * Position.x + u_cameraPosition.x, 0.5 * Position.y + u_cameraPosition.y, Position.z, 1.0);
}