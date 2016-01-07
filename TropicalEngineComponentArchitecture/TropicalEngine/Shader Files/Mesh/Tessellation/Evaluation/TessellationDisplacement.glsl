#ifndef _TESSELLATIONDISPLACEMENT
#define _TESSELLATIONDISPLACEMENT

#include "Utills/Interpolation.glsl"

#version 410

layout(triangles, fractional_odd_spacing, ccw) in;

uniform mat4 u_transformationMatrix;
uniform mat3 u_normalMatrix;
uniform vec3 u_cameraPosition;
uniform mat4 u_cameraMatrix;
uniform mat4 u_projectionMatrix;

uniform sampler2D mat_displacementTexture;
uniform float mat_displacementScale = 0.1;

in vec4 v_vertex_tcs[];
in vec3 v_normal_tcs[];
in vec3 v_tangent_tcs[];
in vec3 v_bitangent_tcs[];
in vec2 v_texcoord_tcs[];

out vec3 v_normal;
out vec3 v_tangent;
out vec3 v_bitangent;
out vec2 v_texcoord;
out vec3 v_eye;

out vec3 v_globalPosition;

void main()
{
	// Interpolate the attributes of the output vertex using the barycentric coordinates
	v_normal = u_normalMatrix * interpolate3D(v_normal_tcs[0], v_normal_tcs[1], v_normal_tcs[2]);
	v_tangent = u_normalMatrix * interpolate3D(v_tangent_tcs[0], v_tangent_tcs[1], v_tangent_tcs[2]);
	v_bitangent = u_normalMatrix * interpolate3D(v_bitangent_tcs[0], v_bitangent_tcs[1], v_bitangent_tcs[2]);
	v_texcoord = interpolate2D(v_texcoord_tcs[0], v_texcoord_tcs[1], v_texcoord_tcs[2]);

	float displacementAmount = texture(mat_displacementTexture, v_texcoord).x;
	vec4 displacement = vec4(v_normal * displacementAmount * mat_displacementScale, 0.0);

	vec4 helper = u_transformationMatrix * (vec4(interpolate3D(v_vertex_tcs[0].xyz, v_vertex_tcs[1].xyz, v_vertex_tcs[2].xyz), 1.0) + displacement);

	v_eye = -vec3((helper)) + u_cameraPosition;
	v_globalPosition = helper.xyz;

	gl_Position = u_projectionMatrix * u_cameraMatrix * (helper);
}

#endif