/**
 * OpenGL 3 - Example 19 - Rendering of the wavefront object
 *
 * @author	Norbert Nopper norbert@nopper.tv
 *
 * Homepage: http://nopper.tv
 *
 * Copyright Norbert Nopper
 */

//obsolete class taken from example

#pragma once
#include "Textures_header.h"


#ifndef WAVEFRONT_H_
#define WAVEFRONT_H_



#define TEXTURE_WIDTH 1024
#define TEXTURE_HEIGHT 768

GLUSboolean initWavefront(GLUSfloat viewMatrix[16], struct LightProperties* light);

GLUSvoid reshapeWavefront(GLUSint width, GLUSint height);

GLUSboolean updateWavefront(GLUSfloat time, GLUSfloat scaleMatrix[16]);

GLUSvoid terminateWavefront(GLUSvoid);

#endif /* WAVEFRONT_H_ */
