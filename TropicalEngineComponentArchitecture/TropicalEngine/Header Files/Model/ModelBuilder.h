#pragma once
#include <QtCore\qstring.h>
#include <QtCore\qvector.h>
#include <glm.hpp>

class Model;
class ModelManager;

class ModelBuilder
{
public:
	friend class ModelManager;

	ModelBuilder(void);
	~ModelBuilder(void);

private:
	Model* Load(QString fileUrl);
public:
	Model* Load(QString name, QString fileUrl);
	void CalculateTangentsBitangents(QVector<glm::vec4>& vertices, QVector<glm::vec3>& normals, QVector<glm::vec2>& texcoords, QVector<glm::vec3>& out_tangents, QVector<glm::vec3>& out_bitangents);

	Model* CreateTriangle(QString name);
	Model* CreatePlane(QString name, float sizeX = 1.0f, float sizeY = 1.0f, int subdivisionsX = 1, int subdivisionsY = 1);
	Model* CreateBox(QString name, float sizeX = 1.0f, float sizeY = 1.0f, float sizeZ = 1.0f, int subdivisionsX = 1, int subdivisionsY = 1, int subdivisionsZ = 1);
	Model* CreateBox(QString name, glm::vec3 size, int subdivisionsX = 1, int subdivisionsY = 1, int subdivisionsZ = 1);
	Model* CreateBox(QString name, glm::vec3 size, glm::vec3 subdivisions);
	Model* CreateCylinder(QString name, float radius = 1.0f, float height = 2.0f, int subdivisionsAxis = 20, int subdivisionsHeight = 1);
	Model* CreateCone(QString name, float radius = 1.0f, float height = 2.0f, int subdivisionsAxis = 20, int subdivisionsHeight = 1);
	Model* CreateSphere(QString name, float radius = 1.0f, int subdivisionsAxis = 20, int subdivisionsHeight = 20);
	Model* CreateTorus(QString name, float radius = 1.0f, float segmentRadius = 0.4f, int subdivisionsAxis = 20, int subdivisionsHeight = 20);
};
