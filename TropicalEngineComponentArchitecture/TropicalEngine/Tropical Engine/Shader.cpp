#include <QtCore\qfile.h>
#include <QtCore\qtextstream.h>
#include <QtCore\qdebug.h>
#include "ShaderManager.h"
#include "Shader.h"

Shader* Shader::nullShader = nullptr;

Shader::Shader(QString vertexShader, QString fragmentShader, QString name):defaultMaterial(this, nullptr, name)
{
	///TODO: implement it.

	shaderProgram = glCreateProgram();

    if (shaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
    
	AddShader(vertexShader, GL_VERTEX_SHADER);
	AddShader(fragmentShader, GL_FRAGMENT_SHADER);

	GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		QString error = *ErrorLog;
        exit(1);
	}

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

	vertexLocation = glGetAttribLocation(this->shaderProgram, "a_vertex");
	normalLocation = glGetAttribLocation(this->shaderProgram, "a_normal");
	tangentLocation = glGetAttribLocation(this->shaderProgram, "a_tangent");
	bitangentLocation = glGetAttribLocation(this->shaderProgram, "a_bitangent");
	texcoordLocation = glGetAttribLocation(this->shaderProgram, "a_texcoord");

	modelMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_modelMatrix");
	normalMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_normalMatrix");
	cameraMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_cameraMatrix");

	ShaderManager::Instance().Load(this, name);
}


Shader::~Shader(void)
{
	///TODO: implement it.
}

GLuint Shader::getShaderProgram()
{
	return shaderProgram;
}

GLuint Shader::getVertexLocation()
{
	return vertexLocation;
}

GLuint Shader::getNormalLocation()
{
	return normalLocation;
}

GLuint Shader::getTangentLocation()
{
	return tangentLocation;
}

GLuint Shader::getBitangentLocation()
{
	return bitangentLocation;
}

GLuint Shader::getTexcoordLocation()
{
	return texcoordLocation;
}

GLuint Shader::getModelMatrixLocation()
{
	return modelMatrixLocation;
}

GLuint Shader::getNormalMatrixLocation()
{
	return normalMatrixLocation;
}

GLuint Shader::getCameraMatrixLocation()
{
	return cameraMatrixLocation;
}

void Shader::AddShader(QString shaderFile, GLenum shaderType)
{
	GLuint ShaderObj = glCreateShader(shaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", shaderType);
        exit(0);
    }

	QFile f(shaderFile);
	if (!f.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << f.errorString();
		return;	//if it will go in here, everything will fuck up.
	}
    QTextStream in(&f);
	QByteArray shaderArray =  in.readAll().toLocal8Bit();
	char* shaderText = new char[shaderArray.size() + 1];
	strcpy_s(shaderText, shaderArray.size() + 1, shaderArray.data());

    const GLchar* p[1];
    p[0] = shaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(shaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
        exit(1);
    }

	glAttachShader(this->shaderProgram, ShaderObj);
}