#version 410

layout(triangles, equal_spacing, ccw) in;

uniform mat4 u_transformationMatrix;	//should be modelview and projection instead of model viewproection
uniform mat3 u_normalMatrix;
uniform mat4 u_cameraMatrix;
uniform mat4 u_projectionMatrix;

uniform sampler2D mat_dispacementTexture;
uniform float mat_displacementScale;

in vec4 v_vertex_tcs[];
in vec3 v_normal_tcs[];
in vec3 v_tangent_tcs[];
in vec3 v_bitangent_tcs[];
in vec2 v_texcoord_tcs[];

//out vec3 v_vertex;
out vec3 v_normal;
out vec3 v_tangent;
out vec3 v_bitangent;
out vec2 v_texcoord;
out vec3 v_eye;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main()
{
	// Interpolate the attributes of the output vertex using the barycentric coordinates
    v_normal = u_normalMatrix * normalize(interpolate3D(v_normal_tcs[0], v_normal_tcs[1], v_normal_tcs[2]));
	v_tangent = u_normalMatrix * normalize(interpolate3D(v_tangent_tcs[0], v_tangent_tcs[1], v_tangent_tcs[2]));
	v_bitangent = u_normalMatrix * normalize(interpolate3D(v_bitangent_tcs[0], v_bitangent_tcs[1], v_bitangent_tcs[2]));
	v_texcoord = interpolate2D(v_texcoord_tcs[0], v_texcoord_tcs[1], v_texcoord_tcs[2]);

    vec4 helper = u_transformationMatrix * vec4(interpolate3D(v_vertex_tcs[0].xyz, v_vertex_tcs[1].xyz, v_vertex_tcs[2].xyz), 1.0);

	float displacementAmount = texture(mat_dispacementTexture, v_texcoord).x;
    vec4 displacement = vec4(v_normal * displacementAmount * mat_displacementScale, 0.0);

	v_eye = -vec3(u_cameraMatrix * (helper + displacement));

    gl_Position = u_projectionMatrix * u_cameraMatrix * (helper + displacement);
}