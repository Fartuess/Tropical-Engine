#include <QtCore\qfile.h>
#include <QtCore\qtextstream.h>
#include <QtCore\qdebug.h>
#include "ShaderManager.h"
#include "Shader.h"

#include "TropicalEngineApplication.h"

Shader* Shader::nullShader = nullptr;

Shader::Shader(QString vertexShader, QString fragmentShader, QString name)
{
	///TODO: implement it.
	this->name = name;
	subprograms = new QVector<GLuint>();
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

	modelMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_transformationMatrix");
	normalMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_normalMatrix");
	cameraMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_cameraMatrix");

	dirLightVectorLocation = glGetUniformLocation(this->shaderProgram, "u_lightVector");
	dirLightColorLocation = glGetUniformLocation(this->shaderProgram, "u_lightColor");
	dirLightBrightnessLocation = glGetUniformLocation(this->shaderProgram, "u_lightBrightness");
	dirLightAmbientLocation = glGetUniformLocation(this->shaderProgram, "u_lightAmbient");

	setUpMaterialParameters();
	defaultMaterial = new Material(this, nullptr, QString(name + "_mat"));
	TropicalEngineApplication::instance()->shaderManager->Load(this, name);
}

Shader::Shader(QMap<QString, GLuint> subshaders, QString name)
{
	///TODO: implement it.
	this->name = name;
	subprograms = new QVector<GLuint>();
	shaderProgram = glCreateProgram();

    if (shaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

	foreach(QString subshader, subshaders.keys())
	{
		AddShader(subshader, subshaders[subshader]);
	}

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

	modelMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_transformationMatrix");
	normalMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_normalMatrix");
	cameraMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_cameraMatrix");

	dirLightVectorLocation = glGetUniformLocation(this->shaderProgram, "u_lightVector");
	dirLightColorLocation = glGetUniformLocation(this->shaderProgram, "u_lightColor");
	dirLightBrightnessLocation = glGetUniformLocation(this->shaderProgram, "u_lightBrightness");
	dirLightAmbientLocation = glGetUniformLocation(this->shaderProgram, "u_lightAmbient");

	setUpMaterialParameters();
	defaultMaterial = new Material(this, nullptr, QString(name + "_mat"));
	TropicalEngineApplication::instance()->shaderManager->Load(this, name);
}

void Shader::setUpMaterialParameters()
{
	materialParameters = new QMap<QString, QPair<GLenum, GLuint>>();
	for(int j = 0; j < subprograms->size(); j++)
	{
		GLint uniformCount = -1;
		GLenum glErr = glGetError();
		GLenum t0 = glErr;
		glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniformCount);
		for(int i = 0; i < uniformCount; i++)
		{
			GLchar nameChar[128];// = new GLchar;
			GLsizei nameLenght;
			GLenum type;
			glGetActiveUniform(shaderProgram, i, 128, &nameLenght, nullptr, &type, nameChar);
			QString nameString = QString(nameChar);
 			if(nameString.startsWith("mat_"))
			{
				//nameString.remove(0, 4);
				materialParameters->insert(nameString, QPair<GLenum, GLuint>(type, i));	//make sure that 'i' is the same as desirable uniform location;
			}
		}
	}
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

GLenum Shader::getParameterType(QString name)
{
	return (*materialParameters)[name].first;
}

GLuint Shader::getParameterLocation(QString name)
{
	return (*materialParameters)[name].second;
}

const QMap<QString, QPair<GLenum, GLuint>>& Shader::getMaterialParameters()
{
	return *materialParameters;
}

Material* Shader::getCurrentMaterial()
{
	return currentMaterial;
}

void Shader::AddShader(QString shaderFile, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0) {
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
    glShaderSource(shaderObj, 1, p, Lengths);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
        exit(1);
    }

	glAttachShader(this->shaderProgram, shaderObj);
	subprograms->append(shaderObj);
}

void Shader::Use()
{
	if(this != TropicalEngineApplication::instance()->shaderManager->getCurrentShader())
	{
		glUseProgram(shaderProgram);
		TropicalEngineApplication::instance()->shaderManager->setCurrentShader(this);
	}
}

QString Shader::toXML()
{
	///TODO: implement it.
	QString XMLString = QString(getIndent() + "<Shader name = \"" + name + "\">\n");
	increaseIndent();
	///TODO: save information about subshader filepaths
	//foreach(subshader
	XMLString += defaultMaterial->toXML();
	decreaseIndent();
	XMLString += QString(getIndent() + "</Shader>\n");

	return XMLString;
}