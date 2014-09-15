#version 330

uniform vec3 u_lightVector;
uniform vec3 u_lightColor;
uniform float u_lightBrightness;
uniform float u_lightAmbient;
uniform sampler2D mat_diffuseTexture;
uniform sampler2D mat_normalTexture;
uniform sampler2D mat_heightTexture;
uniform float mat_bumpScale = 0.1;

in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec3 v_eye;
in vec2 v_texcoord;

out vec4 FragColor;

void main()
{
	mat3 TBN = transpose(mat3(v_tangent, v_bitangent, v_normal));

	vec3 lightdir_ts = normalize(TBN * u_lightVector);
	
	// We are at height bumpScale.  March forward until we hit a hair or the 
    // base surface.  Instead of dropping down discrete y-voxels we should be
    // marching in texels and dropping our y-value accordingly (TODO: fix)
    float height = 1.0;

    // Number of height divisions
    float numSteps = 45;	//originally 5

    /** Texture coordinate marched forward to intersection point */
    vec2 offsetCoord = v_texcoord;
    float NB = texture2D(mat_heightTexture, offsetCoord).r;

    vec3 tsE = normalize(TBN * v_eye);

    // Increase steps at oblique angles
    // Note: tsE.z = N dot V
    numSteps = mix(numSteps*2, numSteps, tsE.z);

    // We have to negate tsE because we're walking away from the eye.
    //vec2 delta = vec2(-_tsE.x, _tsE.y) * bumpScale / (_tsE.z * numSteps);
    float step;
    vec2 delta;


    // Constant in z
    step = 1.0 / numSteps;
    delta = vec2(-tsE.x, tsE.y) * mat_bumpScale / (tsE.z * numSteps);

        // Can also step along constant in xy; the results are essentially
        // the same in each case.
        // delta = 1.0 / (25.6 * numSteps) * vec2(-tsE.x, tsE.y);
        // step = tsE.z * bumpScale * (25.6 * numSteps) / (length(tsE.xy) * 400);

    while (NB < height) {
        height -= step;
        offsetCoord += delta;
        NB = texture2D(mat_heightTexture, offsetCoord).r;
    }

    height = NB;

    // Choose the color at the location we hit
    const vec3 texelcolor = texture2D(mat_diffuseTexture, offsetCoord).rgb;

    vec3 tsL = normalize(lightdir_ts);

    // Use the normals out of the bump map
    vec3 tsN = texture2D(mat_normalTexture, offsetCoord).rgb * 2 - 1;
	//vec3 tsN = normalize(v_normal);

    // Smooth normals locally along gradient to avoid making slices visible.
    // The magnitude of the step should be a function of the resolution and
    // of the bump scale and number of steps.
//    tsN = normalize(texture2D(normalBumpMap, offsetCoord + vec2(tsN.x, -tsN.y) * mipScale).xyz * 2 - 1 + tsN);

    const vec3 tsH = normalize(tsL + normalize(tsE));

    const float NdotL = max(0, dot(tsN, tsL));
    const float NdotH = max(0, dot(tsN, tsH));
    float spec = pow(NdotH, 5);

    //vec3 lightColor = vec3(1.5, 1.5, 1) * 0.9;
    //vec3 ambient = vec3(0.4, 0.4, 0.6) * 1.4;

	vec3 color = texelcolor * u_lightAmbient * u_lightColor;

    //float selfShadow = 0;
	float selfShadow = 1;	//disabled selfshadowing

    // Don't bother checking for self-shadowing if we're on the
    // back side of an object.
    if (NdotL > 0) 
	{

        // Trace a shadow ray along the light vector.
        const int numShadowSteps = int(mix(60, 5 ,tsL.z));
        step = 1.0 / numShadowSteps;
        delta = vec2(tsL.x, -tsL.y) * mat_bumpScale / (numShadowSteps * tsL.z);

        // We start one iteration out to avoid shadow acne 
        // (could start bumped a little without going
        // a whole iteration).
        height = NB + step * 0.1;

        while ((NB < height) && (height < 1)) {
            height += step;
            offsetCoord += delta;
            NB = texture2D(mat_heightTexture, offsetCoord).r;
        }

        // We are in shadow if we left the loop because
        // we hit a point
		if(NB < height)
		{
			selfShadow = 1.0f;
		}

        // Shadows will make the whole scene darker, so up the light contribution
        //lightColor = lightColor * 1.2;

		color += texelcolor * NdotL * selfShadow * u_lightColor * u_lightBrightness;
		color += 0.2 * spec * selfShadow * u_lightColor * u_lightBrightness;
    }

    FragColor = vec4(color, 1.0f);
}