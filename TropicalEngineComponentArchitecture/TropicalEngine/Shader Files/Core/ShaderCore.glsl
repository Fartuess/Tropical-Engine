#ifndef _SHADERCORE
#define _SHADERCORE

/**
  * \brief Shader Core. It requires LightingModel module, BlendMode module and SurfaceShader module to create final shader.
  */
void main()
{
	//in case if surface definition shader haven't specified it.
	g_normal = normalize(v_normal);
	g_eye = normalize(v_eye);
#ifdef TANGENTSPACE
	g_tangent = normalize(v_tangent);
	g_bitangent = normalize(v_bitangent);
#endif

	//in case if surface definition shafer haven't specified it.
#ifdef TEXTURECOORDINATES
	g_texcoord = v_texcoord;
#endif

	//Blending for masked happens earlier as discarding prevents from uneccesary computation.
//#ifdef BLENDMASKED
//	blend();
//#endif
	processSurface();

	//Calculate lighting only for Lit lighting models.
#ifndef UNLIT
	calculateLighting();
	finalizeLightingModel();
#endif
	//If surface shader uses emissive then adds it to the result.
#ifdef EMISSIVEINPUT
	g_color += g_emissiveInput;
#endif

	//Final blending happens here as it requires having final color calculated.
	blend();
}

#endif