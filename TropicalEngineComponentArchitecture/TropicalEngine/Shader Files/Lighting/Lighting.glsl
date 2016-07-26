#ifndef _LIGHTING
#define _LIGHTING

#ifndef UNLIT

// private
void calculateAmbientLighting()
{
	g_ambientChannel = u_lightAmbient * u_lightAmbientColor;
}

// private
LightingResult calculateDirectionalLighting()
{
	vec3 lightVector = normalize(u_lightVector);

	return calculateLightingModel(lightVector, u_lightColor, u_lightBrightness, g_eye);
}

// private
LightingResult calculatePointLighting(PointLight light)
{

	vec3 lightVector = normalize(calculatePointLightVector(light, v_globalPosition));
	float brightness = calculatePointLightBrightness(light, v_globalPosition);

	return calculateLightingModel(lightVector, light.color, brightness, g_eye);
}

// private
LightingResult calculateSpotLighting(SpotLight light)
{
	vec3 lightVector = normalize(calculateSpotLightVector(light, v_globalPosition));
	float brightness = calculateSpotLightBrightness(light, v_globalPosition, lightVector);

	return calculateLightingModel(lightVector, light.color, brightness, g_eye);
}

/**
  * Calculates light for shader. Module requires having some LightingModel module attached.
  */
void calculateLighting()
{
	LightingResult helperLightingResult = LightingResult(vec3(0.0), vec3(0.0));

	calculateAmbientLighting();
	helperLightingResult = calculateDirectionalLighting();
	g_lightingResult.diffuse += helperLightingResult.diffuse;
	g_lightingResult.specular += helperLightingResult.specular;
	for (int i = 0; i < u_pointLights.length(); i++)
	{
		helperLightingResult = calculatePointLighting(u_pointLights[i]);
		g_lightingResult.diffuse += helperLightingResult.diffuse;
		g_lightingResult.specular += helperLightingResult.specular;
	}
	for (int i = 0; i < u_spotLights.length(); i++)
	{
		helperLightingResult = calculateSpotLighting(u_spotLights[i]);
		g_lightingResult.diffuse += helperLightingResult.diffuse;
		g_lightingResult.specular += helperLightingResult.specular;
	}

#ifdef CUSTOMLIGHTING
	helperLightingResult = calculateCustomLighting();
	g_lightingResult.diffuse += helperLightingResult.diffuse;
	g_lightingResult.specular += helperLightingResult.specular;
#endif
}

#endif

#endif