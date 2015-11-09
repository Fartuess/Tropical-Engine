#ifndef _STEEPPARALLAXMAPPING
#define _STEEPPARALLAXMAPPING

#define TEXTURECOORDINATES
#define TANGENTSPACE

void steepParallaxMap(in sampler2D heightMap)
{
	TBN = transpose(mat3(v_tangent, v_bitangent, v_normal));

	float height = 1.0;

	float numSteps = 15;	///TODO: Make this value non hardcoded or mor adaptive.

	vec2 offsetCoord = g_texcoord;
	float NB = texture2D(heightMap, offsetCoord).r;

	vec3 tsE = normalize(TBN * v_eye);

	numSteps = mix(numSteps * 4, numSteps, tsE.z * tsE.z);

	float step = 1.0 / numSteps;
	vec2 delta = vec2(-tsE.x, tsE.y) * mat_bumpScale / (tsE.z * numSteps);

	while (NB < height) {
		height -= step;
		offsetCoord += delta;
		NB = texture2D(mat_heightTexture, offsetCoord).r;
	}

	float smallStep = -step / 10.0;
	while (NB > height)
	{
		height -= smallStep;
		offsetCoord += delta * (smallStep / step);
		NB = texture2D(mat_heightTexture, offsetCoord).r;
	}
	if (NB < height)
	{
		smallStep = step / 30.0;
		height -= smallStep;
		offsetCoord += delta * (smallStep / step);
		NB = texture2D(mat_heightTexture, offsetCoord).r;
	}

	g_texcoord = offsetCoord;
}

#endif