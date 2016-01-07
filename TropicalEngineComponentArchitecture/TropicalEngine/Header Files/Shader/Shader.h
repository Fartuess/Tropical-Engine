#pragma once
#include <GL/glew.h>

#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtCore/qmap.h>

#include <Serialization/ISerializableJSON.h>

#include "Material.h"

namespace TropicalEngine
{

	class Shader : public ISerializableJSON
	{
	public:
		TYPENAME("Shader")

			friend class ShaderManager;

		Material* defaultMaterial;

		//temporarily public
		GLuint shaderProgram;
		QMap<QString, GLuint> subprograms;	///TODO: Value is shader type from now. Not it's address in GPU?

		/// TODO: Make light locations more organised.
		//temporarily public
		GLuint dirLightVectorLocation;
		GLuint dirLightColorLocation;
		GLuint dirLightBrightnessLocation;
		GLuint dirLightAmbientLocation;

		QVector<GLuint> pointLightPositionLocations;
		QVector<GLuint> pointLightColorLocations;
		QVector<GLuint> pointLightBrightnessLocations;
		QVector<GLuint> pointLightRadiusLocations;
		QVector<GLuint> pointLightAttenuationLocations;

		QVector<GLuint> spotLightPositionLocations;
		QVector<GLuint> spotLightDirectionLocations;
		QVector<GLuint> spotLightColorLocations;
		QVector<GLuint> spotLightBrightnessLocations;
		QVector<GLuint> spotLightRadiusLocations;
		QVector<GLuint> spotLightAttenuationLocations;
		QVector<GLuint> spotLightOuterAngleLocations;
		QVector<GLuint> spotLightInnerAngleLoactions;

		GLuint drawingMode;

		static Shader* nullShader;

		Shader(QString vertexShader, QString fragmentShader, QString name, class ShaderManager* manager = nullptr);
		Shader(QMap<QString, GLuint> subshaders, QString name);
		~Shader(void);

		static Shader* createShaderFromSources(QString vertexSource, QString tcsSource, QString tesSource, QString fragmentSource, QString name);

		static QString PreprocessShaderFile(QString shaderFile);

		void setUpLightParameters();
		void setUpMaterialParameters();

		QString getName();
		void setName(QString name);

		GLuint getShaderProgram();
		GLuint getVertexLocation();
		GLuint getNormalLocation();
		GLuint getTangentLocation();
		GLuint getBitangentLocation();
		GLuint getTexcoordLocation();

		GLuint getModelMatrixLocation();
		GLuint getNormalMatrixLocation();
		GLuint getCameraPositionLocation();
		GLuint getCameraMatrixLocation();
		GLuint getProjectionMatrixLocation();

		GLenum getParameterType(QString name);
		GLuint getParameterLocation(QString name);
		const QMap<QString, QPair<GLenum, GLuint>>& getMaterialParameters();

		Material* getCurrentMaterial();

		void Use();

		QJsonObject toJSON() override;
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		QString name;

		QMap<QString, QPair<GLenum, GLuint>>* materialParameters;
		Material* currentMaterial;

		Shader(QString name, GLuint drawingMode = GL_TRIANGLES);

		//temporary define made so program won't break apart.
#define AddShader(shaderFile, shaderType) AddShaderFile(shaderFile, shaderType)
		void AddShaderFile(QString shaderFile, GLenum shaderType);
		void AddShaderSource(QString shaderSource, GLenum shaderType);
		void FinalizeShader();

	private:
		GLuint vertexLocation;
		GLuint normalLocation;
		GLuint tangentLocation;
		GLuint bitangentLocation;
		GLuint texcoordLocation;

		GLuint modelMatrixLocation;
		GLuint normalMatrixLocation;
		GLuint cameraPositionLocation;
		GLuint cameraMatrixLocation;
		GLuint projectionMatrixLocation;
	};

}