#pragma once

#include "Utility_header.h"
#include "Models_header.h"

	TextureManager* tManager;

	Model::Model(Vec3* translate, Vec3* rotate, Vec3* scale, char* mesh)
	{
		_translate[0]=translate->x;
		_translate[1]=translate->y;
		_translate[2]=translate->z;

		_rotate[0]=rotate->x;
		_rotate[1]=rotate->y;
		_rotate[2]=rotate->z;

		_scale[0]=scale->x;
		_scale[1]=scale->y;
		_scale[2]=scale->z;

		Mesh=mesh;
		texture=TextureManager::textures.find("default")->second;
		this->texture2=TextureManager::textures.find("default_spec")->second;
		this->texture3 = TextureManager::textures.find("default_n")->second;
	}

	Model::Model(Vec3* translate, Vec3* rotate, Vec3* scale, char* mesh, char* texture)
	{
		_translate[0]=translate->x;
		_translate[1]=translate->y;
		_translate[2]=translate->z;

		_rotate[0]=rotate->x;
		_rotate[1]=rotate->y;
		_rotate[2]=rotate->z;

		_scale[0]=scale->x;
		_scale[1]=scale->y;
		_scale[2]=scale->z;

		Mesh=mesh;
		this->texture=TextureManager::textures.find(texture)->second;
		this->texture2=this->texture;
		this->texture3 = TextureManager::textures.find("normal")->second;
	}

	Model::Model(Vec3* translate, Vec3* rotate, Vec3* scale, char* mesh, char* texture, char* texture2)
	{
		_translate[0]=translate->x;
		_translate[1]=translate->y;
		_translate[2]=translate->z;

		_rotate[0]=rotate->x;
		_rotate[1]=rotate->y;
		_rotate[2]=rotate->z;

		_scale[0]=scale->x;
		_scale[1]=scale->y;
		_scale[2]=scale->z;

		Mesh=mesh;
		this->texture=TextureManager::textures.find(texture)->second;
		this->texture2=TextureManager::textures.find(texture2)->second;
		this->texture3 = TextureManager::textures.find("normal")->second;
	}

	Model::Model(Vec3* translate, Vec3* rotate, Vec3* scale, char* mesh, char* texture, char* texture2, char* texture3)
	{
		_translate[0]=translate->x;
		_translate[1]=translate->y;
		_translate[2]=translate->z;

		_rotate[0]=rotate->x;
		_rotate[1]=rotate->y;
		_rotate[2]=rotate->z;

		_scale[0]=scale->x;
		_scale[1]=scale->y;
		_scale[2]=scale->z;

		Mesh=mesh;
		this->texture=TextureManager::textures.find(texture)->second;
		this->texture2=TextureManager::textures.find(texture2)->second;
		this->texture3 = TextureManager::textures.find(texture3)->second;
	}

	Model::Model(Vec3* translate, Vec3* rotate, Vec3* scale, GLUSshape* mesh)
	{
		_translate[0]=translate->x;
		_translate[1]=translate->y;
		_translate[2]=translate->z;

		_rotate[0]=rotate->x;
		_rotate[1]=rotate->y;
		_rotate[2]=rotate->z;

		_scale[0]=scale->x;
		_scale[1]=scale->y;
		_scale[2]=scale->z;
		
		Mesh = NULL;
		shape = mesh;
		texture=TextureManager::textures.find("default")->second;
		this->texture2=texture;
		this->texture3 = TextureManager::textures.find("default_n")->second;
	}

	GLUSboolean Model::initWavefront(GLUSfloat viewMatrix[16], struct LightProperties* light)
	{
		// Color material with white specular color.
		struct MaterialProperties _material = { { 0.0f, 0.5f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 20.0f };

		//* temp fix */texture3 = TextureManager::textures.find("default_n")->second;

		GLUStextfile _vertexSource;
		GLUStextfile _fragmentSource;

		GLUSshape _wavefrontObj;

		_viewMatrix = viewMatrix;

		_light = light;

		//texture=tManager->textures.find("default")->second;
		//texture= new Texture("GenericTiles.tga");

		//glActiveTexture(GL_TEXTURE2);
		//glBindTexture(GL_TEXTURE_2D, texture->_texture);
		//glUniform1i(_textureLocation, 1);

		//

		//take shaders somewhere else
		glusLoadTextFile("../TropicalApartmentOpenGL3/shader/bumpVS.vert.glsl", &_vertexSource);
		glusLoadTextFile("../TropicalApartmentOpenGL3/shader/phongblinnbump.frag.glsl", &_fragmentSource);

		glusBuildProgramFromSource(&_program, (const GLUSchar**) &_vertexSource.text, 0, 0, 0, (const GLUSchar**) &_fragmentSource.text);

		glusDestroyTextFile(&_vertexSource);
		glusDestroyTextFile(&_fragmentSource);

		//

		_projectionMatrixLocation = glGetUniformLocation(_program.program, "u_projectionMatrix");
		_modelViewMatrixLocation = glGetUniformLocation(_program.program, "u_modelViewMatrix");
		_normalMatrixLocation = glGetUniformLocation(_program.program, "u_normalMatrix");

		_lightLocations.directionLocation = glGetUniformLocation(_program.program, "u_light.direction");
		_lightLocations.ambientColorLocation = glGetUniformLocation(_program.program, "u_light.ambientColor");
		_lightLocations.diffuseColorLocation = glGetUniformLocation(_program.program, "u_light.diffuseColor");
		_lightLocations.specularColorLocation = glGetUniformLocation(_program.program, "u_light.specularColor");

		_materialLocation.ambientColorLocation = glGetUniformLocation(_program.program, "u_material.ambientColor");
		_materialLocation.diffuseColorLocation = glGetUniformLocation(_program.program, "u_material.diffuseColor");
		_materialLocation.specularColorLocation = glGetUniformLocation(_program.program, "u_material.specularColor");
		_materialLocation.specularExponentLocation = glGetUniformLocation(_program.program, "u_material.specularExponent");

		_textureLocation = glGetUniformLocation(_program.program, "u_texture");
		_specularLocation = glGetUniformLocation(_program.program, "u_specular");
		_normalMapLocation = glGetUniformLocation(_program.program, "u_normalMap");

		_vertexLocation = glGetAttribLocation(_program.program, "a_vertex");
		_normalLocation = glGetAttribLocation(_program.program, "a_normal");
		_texCoordLocation = glGetAttribLocation(_program.program, "a_texCoord");
		_tangentLocation = glGetAttribLocation(_program.program, "a_tangent");
		_bitangentLocation = glGetAttribLocation(_program.program, "a_bitangent");

		//

		// Use a helper function to load an wavefront object file.
		if(Mesh !=  NULL)
		{
			glusLoadObjFile(Mesh, &_wavefrontObj);
		}
		else
		{
			if(shape != NULL)
			{
				_wavefrontObj = *shape;
			}
		}

		_numberVertices = _wavefrontObj.numberVertices;

		

		glGenBuffers(1, &_verticesVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);
		glBufferData(GL_ARRAY_BUFFER, _wavefrontObj.numberVertices * 4 * sizeof(GLfloat), (GLfloat*) _wavefrontObj.vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &_normalsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _normalsVBO);
		glBufferData(GL_ARRAY_BUFFER, _wavefrontObj.numberVertices * 3 * sizeof(GLfloat), (GLfloat*) _wavefrontObj.normals, GL_STATIC_DRAW);

		glGenBuffers(1, &_texCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, _wavefrontObj.numberVertices * 2 * sizeof(GLfloat), (GLfloat*) _wavefrontObj.texCoords, GL_STATIC_DRAW);
		
		glGenBuffers(1, &_tangentVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _tangentVBO);
		glBufferData(GL_ARRAY_BUFFER, _wavefrontObj.numberVertices * 3 * sizeof(GLfloat), (GLfloat*) _wavefrontObj.tangents, GL_STATIC_DRAW);

		glGenBuffers(1, &_bitangentVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _bitangentVBO);
		glBufferData(GL_ARRAY_BUFFER, _wavefrontObj.numberVertices * 3 * sizeof(GLfloat), (GLfloat*) _wavefrontObj.bitangents, GL_STATIC_DRAW);

		//glusCalculateTangentSpacef(&_wavefrontObj);
		_wavefrontObj.tangents;
		_wavefrontObj.bitangents;

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		//glGenTextures(1, &texture->_texture);

		glusDestroyShapef(&_wavefrontObj);

		//

		glUseProgram(_program.program);

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);
		glVertexAttribPointer(_vertexLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(_vertexLocation);

		glBindBuffer(GL_ARRAY_BUFFER, _normalsVBO);
		glVertexAttribPointer(_normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(_normalLocation);

		glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVBO);
		glVertexAttribPointer(_texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(_texCoordLocation);

		glBindBuffer(GL_ARRAY_BUFFER, _tangentVBO);
		glVertexAttribPointer(_tangentLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(_tangentLocation);

		glBindBuffer(GL_ARRAY_BUFFER, _bitangentVBO);
		glVertexAttribPointer(_bitangentLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(_bitangentLocation);

		//

		glusVector3Normalizef(_light->direction);

		// Set up light ...
		// Direction is set later
		glUniform4fv(_lightLocations.ambientColorLocation, 1, _light->ambientColor);
		glUniform4fv(_lightLocations.diffuseColorLocation, 1, _light->diffuseColor);
		glUniform4fv(_lightLocations.specularColorLocation, 1, _light->specularColor);

		// ... and material values.
		glUniform4fv(_materialLocation.ambientColorLocation, 1, _material.ambientColor);
		glUniform4fv(_materialLocation.diffuseColorLocation, 1, _material.diffuseColor);
		glUniform4fv(_materialLocation.specularColorLocation, 1, _material.specularColor);
		glUniform1f(_materialLocation.specularExponentLocation, _material.specularExponent);

		//

		//glBindTexture(GL_TEXTURE_2D, texture->_texture);
		//glUniform1i(_textureLocation, 0);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClearDepth(1.0f);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);

		return GLUS_TRUE;
	}

	GLUSvoid Model::reshapeWavefront(GLUSint width, GLUSint height)
	{
		GLfloat projectionMatrix[16];

		glViewport(0, 0, width, height);

		glusPerspectivef(projectionMatrix, 40.0f, (GLfloat) width / (GLfloat) height, 1.0f, 10000.0f);

		glUseProgram(_program.program);

		// Just pass the projection matrix. The final matrix is calculated in the shader.
		glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
	}

	GLUSboolean Model::updateWavefront(Vec3* translate, Vec3* rotate, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16])
	{
		//static GLfloat angle = 0.0f;

		//_translate[0]=translate->x;
		//_translate[1]=translate->y;
		//_translate[2]=translate->z;

		GLfloat modelViewMatrix[16];
		GLfloat normalMatrix[9];
		//GLfloat texcoordMatrix[4];// <-New
		GLfloat lightMatrix[16];
		GLfloat lightDirection[3];

		_lightLocations.diffuseColorLocation = glGetUniformLocation(_program.program, "u_light.diffuseColor");

		// Set up light ...
		// Direction is set later
		//glUniform4fv(g_lightLocations.ambientColorLocation, 1, g_light->ambientColor);
		//glUniform4fv(g_lightLocations.diffuseColorLocation, 1, g_light->diffuseColor);
		//glUniform4fv(g_lightLocations.specularColorLocation, 1, g_light->specularColor);



		// Note that the scale matrix is for flipping the model upside down.
		glusMatrix4x4Identityf(modelViewMatrix);
		glusMatrix4x4Multiplyf(modelViewMatrix, modelViewMatrix, scaleMatrix);
		
		//glusMatrix4x4Translatef(modelViewMatrix, 0.0f, 1.25f, 0.0f);
		
		glusMatrix4x4Translatef(modelViewMatrix, _translate[0]+translate->x, _translate[1]+translate->y, _translate[2]+translate->z);
		glusMatrix4x4RotateRzRyRxf(modelViewMatrix, _rotate[2]+rotate->z, _rotate[1]+rotate->y, _rotate[0]+rotate->x);
		glusMatrix4x4Scalef(modelViewMatrix, _scale[0]*scale->x, _scale[1]*scale->y, _scale[2]*scale->z);
		//glusMatrix4x4RotateRyf(modelViewMatrix, angle);
		glusMatrix4x4Multiplyf(modelViewMatrix, _viewMatrix, modelViewMatrix);

		glusMatrix4x4ExtractMatrix3x3f(normalMatrix, modelViewMatrix);

		// Transform light to camera space, as it is currently in world space. Also, flip light upside down depending on scale.
		glusMatrix4x4Multiplyf(lightMatrix, _viewMatrix, scaleMatrix);
		glusMatrix4x4MultiplyVector3f(lightDirection, lightMatrix, _light->direction);

		glUseProgram(_program.program);

		glUniform3fv(_lightLocations.directionLocation, 1, lightDirection);

		glUniformMatrix4fv(_modelViewMatrixLocation, 1, GL_FALSE, modelViewMatrix);
		glUniformMatrix3fv(_normalMatrixLocation, 1, GL_FALSE, normalMatrix);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture->_texture);
		glUniform1i(_textureLocation, 2);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texture2->_texture);
		glUniform1i(_specularLocation, 3);

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, texture3->_texture);
		glUniform1i(_normalMapLocation, 4);

		glBindVertexArray(_vao);

		glDrawArrays(GL_TRIANGLES, 0, _numberVertices);
		//glDrawArrays(GL_LINES, 0, _numberVertices);

		return GLUS_TRUE;
	}

	GLUSvoid Model::terminateWavefront(GLUSvoid)	//not terminating tangentsd, bitangents and texcoords
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (_verticesVBO)
		{
			glDeleteBuffers(1, &_verticesVBO);

			_verticesVBO = 0;
		}

		if (_normalsVBO)
		{
			glDeleteBuffers(1, &_normalsVBO);

			_normalsVBO = 0;
		}

		glBindVertexArray(0);

		if (_vao)
		{
			glDeleteVertexArrays(1, &_vao);

			_vao = 0;
		}

		glUseProgram(0);

		glusDestroyProgram(&_program);
	}
