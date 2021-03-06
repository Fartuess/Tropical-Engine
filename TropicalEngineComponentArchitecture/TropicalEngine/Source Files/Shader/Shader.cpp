#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qdebug.h>
#include <QtCore/qregexp.h>
#include <QtCore/qregularexpression.h>
#include <Shader/ShaderManager.h>
#include <Shader/Shader.h>
#include <Shader/ShaderException.h>
#include <Light/PointLightComponent.h>

namespace TropicalEngine
{

	Shader* Shader::nullShader = nullptr;

	Shader::Shader(QString name, GLuint drawingMode)
	{
		this->name = name;

		this->drawingMode = drawingMode;

		shaderProgram = glCreateProgram();

		if (shaderProgram == NULL)
		{
			throw ShaderException("Error creating shader program", this);
		}
	}

	Shader::Shader(QString vertexShader, QString fragmentShader, QString name, ShaderManager* manager) : Shader(name)
	{
		AddShader(vertexShader, GL_VERTEX_SHADER);
		AddShader(fragmentShader, GL_FRAGMENT_SHADER);

		FinalizeShader();

		if (manager != nullptr)
		{
			manager->Load(this, name);
		}
		else
		{
			ShaderManager::instance().Load(this, name);
		}
	}

	Shader::Shader(QMap<QString, GLuint> subshaders, QString name) : Shader(name)
	{
		for (QString subshader : subshaders.keys())
		{
			AddShader(subshader, subshaders[subshader]);
		}

		FinalizeShader();

		ShaderManager::instance().Load(this, name);
	}

	Shader* Shader::createShaderFromSources(QString vertexSource, QString tcsSource, QString tesSource, QString fragmentSource, QString name)
	{
		Shader* shader = new Shader(name);

		shader->AddShaderSource(vertexSource, GL_VERTEX_SHADER);
		if (!(tcsSource == "" || tesSource == ""))
		{
			shader->drawingMode = GL_PATCHES;
			shader->AddShaderSource(tcsSource, GL_TESS_CONTROL_SHADER);
			shader->AddShaderSource(tesSource, GL_TESS_EVALUATION_SHADER);
		}
		shader->AddShaderSource(fragmentSource, GL_FRAGMENT_SHADER);

		shader->FinalizeShader();

		ShaderManager::instance().Load(shader, name);

		return shader;
	}

	void Shader::setUpLightParameters()
	{
		dirLightVectorLocation = glGetUniformLocation(this->shaderProgram, "u_lightVector");
		dirLightColorLocation = glGetUniformLocation(this->shaderProgram, "u_lightColor");
		dirLightBrightnessLocation = glGetUniformLocation(this->shaderProgram, "u_lightBrightness");
		ambientLightBrightnessLocation = glGetUniformLocation(this->shaderProgram, "u_lightAmbient");
		ambientLightColorLocation = glGetUniformLocation(this->shaderProgram, "u_lightAmbientColor");

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

		spotLightPositionLocations = QVector<GLuint>();
		spotLightDirectionLocations = QVector<GLuint>();
		spotLightColorLocations = QVector<GLuint>();
		spotLightBrightnessLocations = QVector<GLuint>();
		spotLightRadiusLocations = QVector<GLuint>();
		spotLightAttenuationLocations = QVector<GLuint>();
		spotLightOuterAngleLocations = QVector<GLuint>();
		spotLightInnerAngleLoactions = QVector<GLuint>();
		for (int i = 0; i < MAX_SPOT_LIGHT; i++)
		{
			spotLightPositionLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_spotLights[" + QString::number(i) + "].position").toLocal8Bit().data()));
			spotLightDirectionLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_spotLights[" + QString::number(i) + "].direction").toLocal8Bit().data()));
			spotLightColorLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_spotLights[" + QString::number(i) + "].color").toLocal8Bit().data()));
			spotLightBrightnessLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_spotLights[" + QString::number(i) + "].brightness").toLocal8Bit().data()));
			spotLightRadiusLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_spotLights[" + QString::number(i) + "].radius").toLocal8Bit().data()));
			spotLightAttenuationLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_spotLights[" + QString::number(i) + "].attenuation").toLocal8Bit().data()));
			spotLightOuterAngleLocations.append(glGetUniformLocation(this->shaderProgram, QString("u_spotLights[" + QString::number(i) + "].outerAngle").toLocal8Bit().data()));
			spotLightInnerAngleLoactions.append(glGetUniformLocation(this->shaderProgram, QString("u_spotLights[" + QString::number(i) + "].innerAngle").toLocal8Bit().data()));
		}
	}

	void Shader::setUpMaterialParameters()
	{
		materialParameters = new QMap<QString, QPair<GLenum, GLuint>>();

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

			if (nameString.startsWith("mat_"))
			{
				materialParameters->insert(nameString, QPair<GLenum, GLuint>(type, glGetUniformLocation(this->shaderProgram, nameChar)));	// TODO: figure out why +1 is needed.
			}
		}
	}

	Shader::~Shader(void)
	{
		for (GLuint subprogram : subprograms)
		{
			glDetachShader(shaderProgram, subprogram);
			glDeleteShader(subprogram);
		}
		glDeleteProgram(shaderProgram);

		// TODO: Delete Materials using this Shader?
	}

	QString Shader::getName()
	{
		return name;
	}

	void Shader::setName(QString name)
	{
		// TODO: change key name in Shader managers.
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
			return "";	//if it will go in here, everything will go wrong.
			// TODO: Handle it
		}
		QTextStream in(&f);
		QString fileString = in.readAll();

		QRegularExpression includeRegexp = QRegularExpression("#include \"([A-Za-z_./]+)\"");

		QRegularExpressionMatchIterator matches = includeRegexp.globalMatch(fileString);
		QStringList includeFilenames = QStringList();
		//QStringList includeFilenames =match.capturedTexts();

		while (matches.hasNext())
		{
			QRegularExpressionMatch match = matches.next();
			includeFilenames.append(match.captured(1));
		}

		for (QString includeFilename : includeFilenames)
		{
			fileString.replace(QRegularExpression(QString("#include \"" + includeFilename + "\"")), PreprocessShaderFile(QString("./Shader Files/" + includeFilename)));
		}
		return fileString;
	}

	void Shader::AddShaderFile(QString shaderFile, GLenum shaderType)
	{
		AddShaderSource(PreprocessShaderFile(shaderFile), shaderType);
	}

	void Shader::AddShaderSource(QString shaderSource, GLenum shaderType)
	{
		GLuint shaderObj = glCreateShader(shaderType);

		if (shaderObj == NULL)
		{
			throw ShaderException("Error creating shader type " + QString::number(shaderType), this);
		}

		QByteArray shaderArray = shaderSource.toLocal8Bit();
		char* shaderText = new char[shaderArray.size() + 1];
		strcpy_s(shaderText, shaderArray.size() + 1, shaderArray.data());

		const GLchar* p[1];
		p[0] = shaderText;
		GLint Lengths[1];
		Lengths[0] = strlen(shaderText);
		glShaderSource(shaderObj, 1, p, Lengths);
		glCompileShader(shaderObj);
		GLint success;
		glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar InfoLog[1024];
			glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);

			// TODO: Figure out if shader object should be deleted here or leave it for catching code.
			glDeleteShader(shaderObj);

			throw ShaderException("Error compiling shader type " + QString::number(shaderType) + ": " + QString(InfoLog), this);
		}

		glAttachShader(this->shaderProgram, shaderObj);
		subprograms[name + "_" + shaderType] = shaderObj;

	}

	void Shader::Use()
	{
		if (this != ShaderManager::instance().getCurrentShader())
		{
			glUseProgram(shaderProgram);
			ShaderManager::instance().setCurrentShader(this);
		}
	}

	//QString Shader::toXML()
	//{
	//	// TODO: implement it.
	//	QString XMLString = QString(getIndent() + "<Shader name = \"" + name + "\">\n");
	//	increaseIndent();
	//	// TODO: save information about subshader filepaths
	//	//foreach(subshader
	//	XMLString += defaultMaterial->toXML();
	//	decreaseIndent();
	//	XMLString += QString(getIndent() + "</Shader>\n");
	//
	//	return XMLString;
	//}

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

	IDeserializableFromJSON* Shader::fromJSON(QJsonObject JSON)
	{
		// TODO: Implement it!
		return new Shader(*nullShader);
	}

	void Shader::FinalizeShader()
	{
		GLint Success = 0;
		GLchar ErrorLog[1024] = { 0 };

		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success);
		if (!Success)
		{
			glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
			throw ShaderException("Error linking shader program: " + QString(ErrorLog), this);
		}

		glValidateProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &Success);
		if (!Success)
		{
			glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);

			// TODO: Validation checks correctness at moment of creation shader. But shader state might become correct later.

			//throw ShaderException("Invalid shader program: " + QString(ErrorLog), this);
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

		defaultMaterial = new Material(this, QString(name + "_mat"));
	}
}