#pragma once
//#ifndef Model_Included
//#define Model_Included

#include "Utility_header.h"
#include "Models_header.h"


//extern TextureManager* tManager;

class Vec3;

class Model
{
	friend class ModelGenerator;

public:

	GLfloat* _viewMatrix;

	GLUSshaderprogram _program;

/**
 * The location of the projection matrix.
 */
	GLint _projectionMatrixLocation;

/**
 * The location of the model view matrix.
 */
	GLint _modelViewMatrixLocation;
	GLint _normalMatrixLocation;

	GLint _vertexLocation;
	GLint _normalLocation;
	GLint _texCoordLocation;
	GLint _tangentLocation;
	GLint _bitangentLocation;

	GLint _textureLocation;
	GLint _specularLocation;
	GLint _normalMapLocation;

/**
 * The locations for the light properties.
 */
	LightLocations _lightLocations;

/**
 * The locations for the material properties.
 */
	MaterialLocations _materialLocation;

	GLuint _verticesVBO;
	GLuint _normalsVBO;
	GLuint _texCoordsVBO;
	GLuint _tangentVBO;
	GLuint _bitangentVBO;

	GLuint _vao;
	GLuint _numberVertices;


	struct LightProperties* _light;
	
	Texture* texture;
	Texture* texture2;
	Texture* texture3;

	GLUSboolean initWavefront(GLUSfloat viewMatrix[16], struct LightProperties* light);
	GLUSvoid reshapeWavefront(GLUSint width, GLUSint height);
	GLUSboolean updateWavefront(Vec3* translate, Vec3* rotate, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16]);
	GLUSvoid terminateWavefront(GLUSvoid);

	float _translate[3];
	float _rotate[3];
	float _scale[3];
	char* Mesh;
	GLUSshape* shape;

	Model(Vec3* translate, Vec3* rotate, Vec3* scale, char* mesh);
	Model(Vec3* translate, Vec3* rotate, Vec3* scale, char* mesh, char* texture);
	Model(Vec3* translate, Vec3* rotate, Vec3* scale, char* mesh, char* texture, char* texture2);
	Model(Vec3* translate, Vec3* rotate, Vec3* scale, char* mesh, char* texture, char* texture2, char* texture3);

	Model(Vec3* translate, Vec3* rotate, Vec3* scale, GLUSshape* mesh);
	Model(Vec3* translate, Vec3* rotate, Vec3* scale, GLUSshape* mesh, char* texture);
	Model(Vec3* translate, Vec3* rotate, Vec3* scale, GLUSshape* mesh, char* texture, char* texture2);
};

//#endif //Model_Included