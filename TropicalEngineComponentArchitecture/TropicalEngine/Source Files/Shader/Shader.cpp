#include <QtCore\qfile.h>
#include <QtCore\qtextstream.h>
#include <QtCore\qdebug.h>
#include <QtCore\qregexp.h>
#include <QtCore\qregularexpression.h>
#include "Shader\ShaderManager.h"
#include "Shader\Shader.h"
#include "Light\PointLightComponent.h"

#include "TropicalEngineApplication.h"

Shader* Shader::nullShader = nullptr;

Shader::Shader(QString vertexShader, QString fragmentShader, QString name)
{
	///TODO: implement it.
	this->name = name;

	drawingMode = GL_TRIANGLES;

	//subprograms = new QVector<GLuint>();
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
	cameraPositionLocation = glGetUniformLocation(this->shaderProgram, "u_cameraPosition");
	cameraMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_cameraMatrix");
	projectionMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_projectionMatrix");

	setUpLightParameters();
	setUpMaterialParameters();

	defaultMaterial = new Material(this, nullptr, QString(name + "_mat"));
	TropicalEngineApplication::instance()->shaderManager->Load(this, name);
}

Shader::Shader(QMap<QString, GLuint> subshaders, QString name)
{
	///TODO: implement it.
	this->name = name;

	drawingMode = GL_TRIANGLES;

	//subprograms = new QVector<GLuint>();
	shaderProgram = glCreateProgram();

    if (shaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

	for (QString subshader : subshaders.keys())
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
	cameraPositionLocation = glGetUniformLocation(this->shaderProgram, "u_cameraPosition");
	projectionMatrixLocation = glGetUniformLocation(this->shaderProgram, "u_projectionMatrix");

	setUpLightParameters();
	setUpMaterialParameters();

	defaultMaterial = new Material(this, nullptr, QString(name + "_mat"));
	TropicalEngineApplication::instance()->shaderManager->Load(this, name);
}

void Shader::setUpLightParameters()
{
	dirLightVectorLocation = glGetUniformLocation(this->shaderProgram, "u_lightVector");
	dirLightColorLocation = glGetUniformLocation(this->shaderProgram, "u_lightColor");
	dirLightBrightnessLocation = glGetUniformLocation(this->shaderProgram, "u_lightBrightness");
	dirLightAmbientLocation = glGetUniformLocation(this->shaderProgram, "u_lightAmbient");

	pointLightPositionLocations = QVector<GLuint>();
	pointLightColorLocations = QVector<GLuint>();
	pointLightBrightnessLocations = QVector<GLuint>();
	pointLightRadiusLocations = QVector<GLuint>();
	pointLightAttenuationLocations = QVector<GLuint>();

	for (int i = 0; i < MAX_POINT_LIGHT; i++)
	{
		pointLightPositionLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_pointLights[" + QString::number(i) + "].position").toLocal8Bit().data()));
		pointLightColorLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_pointLights[" + QString::number(i) + "].color").toLocal8Bit().data()));
		pointLightBrightnessLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_pointLights[" + QString::number(i) + "].brightness").toLocal8Bit().data()));
		pointLightRadiusLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_pointLights[" + QString::number(i) + "].radius").toLocal8Bit().data()));
		pointLightAttenuationLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_pointLights[" + QString::number(i) + "].attenuation").toLocal8Bit().data()));
	}
}

void Shader::setUpMaterialParameters()
{
	materialParameters = new QMap<QString, QPair<GLenum, GLuint>>();
	//for(int j = 0; j < subprograms->size(); j++)
	//{
		GLint uniformCount = -1;
		GLenum glErr = glGetError();
		GLenum t0 = glErr;
		glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniformCount);
		for (int i = 0; i < uniformCount; i++)
		{
			GLchar nameChar[128];
			GLsizei nameLenght;
			GLenum type;
			GLint size;	//to prevent crash?
			glGetActiveUniform(shaderProgram, i, 128, &nameLenght, &size, &type, nameChar);
			QString nameString = QString(nameChar);

			int test = glGetUniformLocation(this->shaderProgram, nameChar);

			if (test == -1)
			{
				int lol = 5050;
			}

 			if (nameString.startsWith("mat_"))
			{
				//nameString.remove(0, 4);
				
				materialParameters->insert(nameString, QPair<GLenum, GLuint>(type, glGetUniformLocation(this->shaderProgram, nameChar)));	///TODO: figure out why +1 is needed.
			}
		}
	//}
		//test
		//foreach(QString paramname, materialParameters->keys())
		//{
		//	qDebug() << paramname << (*materialParameters)[paramname].first << (*materialParameters)[paramname].second;
		//}
}

Shader::~Shader(void)
{
	///TODO: implement it.
}

QString Shader::getName()
{
	return name;
}

void Shader::setName(QString name)
{
	///TODO: change key name in Shader managers.
	this->name = name;
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

GLuint Shader::getCameraPositionLocation()
{
	return cameraPositionLocation;
}

GLuint Shader::getCameraMatrixLocation()
{
	return cameraMatrixLocation;
}

GLuint Shader::getProjectionMatrixLocation()
{
	return projectionMatrixLocation;
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

QString Shader::PreprocessShaderFile(QString shaderFile)
{
	QFile f(shaderFile);
	if (!f.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << f.errorString();
		return "";	//if it will go in here, everything will fuck up.
	}
    QTextStream in(&f);
	QString fileString = in.readAll();

	QRegularExpression includeRegexp = QRegularExpression("#include \"([A-Za-z_.]+)\"");

	QStringList includeFilenames = QStringList();
	QRegularExpressionMatch match = includeRegexp.match(fileString);

	if (match.hasMatch())
	{
		includeFilenames.append(match.captured(1));
	}

	for (QString includeFilename : includeFilenames)
	{
		//qDebug() << includeFilename;
		fileString.replace(QRegularExpression(QString("#include \"" + includeFilename + "\"")), PreprocessShaderFile(QString("./Shader Files/" + includeFilename)));
	}
	//qDebug() << fileString;
	return fileString;
}

void Shader::AddShader(QString shaderFile, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", shaderType);
        exit(0);
    }

	//QFile f(shaderFile);
	//if (!f.open(QFile::ReadOnly | QFile::Text))
	//{
	//	qDebug() << f.errorString();
	//	return;	//if it will go in here, everything will fuck up.
	//}
    //QTextStream in(&f);
	QByteArray shaderArray =  PreprocessShaderFile(shaderFile).toLocal8Bit();
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
	subprograms[shaderFile] = shaderObj;
}

void Shader::Use()
{
	if (this != TropicalEngineApplication::instance()->shaderManager->getCurrentShader())
	{
		glUseProgram(shaderProgram);
		TropicalEngineApplication::instance()->shaderManager->setCurrentShader(this);
	}
}

QString Shader::GETTYPENAME("Shader");

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

QJsonObject Shader::toJSON()
{
	QJsonObject JSON = QJsonObject();
	JSON["name"] = name;
	QJsonArray subshadersJSON = QJsonArray();
	for (QString subshader : subprograms.keys())
	{
		QJsonObject subshaderJSON = QJsonObject();
		subshaderJSON["url"] = subshader;
		subshaderJSON["type"] = QString::number(subprograms[subshader]);
		subshadersJSON.push_back(subshaderJSON);
	}
	JSON["subshaders"] = subshadersJSON;

	return JSON;
}