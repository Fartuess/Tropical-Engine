#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtCore/qmap.h>
#include <glm.hpp>

#include "ModelImporter/AbstractModelImporter.h"
#include "ModelBuilder/AbstractModelBuilder.h"

class Model;
class ModelManager;

/**
  * Class for building and importing Model assets.
  */
class ModelBuilder
{
public:
	friend class ModelManager;

	/**
	  * \brief Constructor for ModelBuilder class.
	  */
	ModelBuilder(void);

	/**
	  * \brief Destructor for ModelBuilder class.
	  */
	~ModelBuilder(void);

	/**
	  * \brief Loads model.
	  *
	  * Loads and adds model to ModelManager.
	  *
	  * @param name Name of the model to be set.
	  * @param fileUrl path to model file.
	  * @return Loaded Model.
	  */
	Model* Load(QString name, QString fileUrl);

	void CalculateTangentsBitangents(QVector<glm::vec4>& vertices, QVector<glm::vec3>& normals, QVector<glm::vec2>& texcoords, QVector<glm::vec3>& out_tangents, QVector<glm::vec3>& out_bitangents);

	AbstractModelBuilder* getModelBuilder(QString name);

	void AddModelBuilder(AbstractModelBuilder* modelBuilder);

//	/**
//	  * \brief Creates equilateral triangle model.
//	  *
//	  * Creates and adds equilateral triangle model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @return Created Model.
//	  */
//	Model* CreateTriangle(QString name);
//
//	/**
//	  * \brief Creates plane model.
//	  *
//	  * Creates and adds plane model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @param sizeX Size of plane in X dimension.
//	  * @param sizeY Size of plane in Y dimension.
//	  * @param subdivisionsX Number of subdivisions in X dimension.
//	  * @param subdivisionsY Number of subdivisions in Y dimension.
//	  * @return Created Model.
//	  */
//	Model* CreatePlane(QString name, float sizeX = 1.0f, float sizeY = 1.0f, int subdivisionsX = 1, int subdivisionsY = 1);
//
//	/**
//	  * \brief Creates box model.
//	  *
//	  * Creates and adds box model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @param sizeX Size of box in X dimension.
//	  * @param sizeY Size of box in Y dimension.
//	  * @param sizeZ Size of box in Z dimension.
//	  * @param subdivisionsX Number of subdivisions in X dimension.
//	  * @param subdivisionsY Number of subdivisions in Y dimension.
//	  * @param subdivisionsZ Number of subdivisions in Z dimension.
//	  * @return Created Model.
//	  */
//	Model* CreateBox(QString name, float sizeX = 1.0f, float sizeY = 1.0f, float sizeZ = 1.0f, int subdivisionsX = 1, int subdivisionsY = 1, int subdivisionsZ = 1);
//
//	/**
//	  * \brief Creates box model.
//	  *
//	  * Creates and adds box model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @param size Size of box in XYZ dimensions.
//	  * @param subdivisionsX Number of subdivisions in X dimension.
//	  * @param subdivisionsY Number of subdivisions in Y dimension.
//	  * @param subdivisionsZ Number of subdivisions in Z dimension.
//	  * @return Created Model.
//	  */
//	Model* CreateBox(QString name, glm::vec3 size, int subdivisionsX = 1, int subdivisionsY = 1, int subdivisionsZ = 1);
//
//	/**
//	  * \brief Creates box model.
//	  *
//	  * Creates and adds box model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @param size Size of box in XYZ dimensions.
//	  * @param subdivisions Number of subdivisions in XYZ dimension.
//	  * @return Created Model.
//	  */
//	Model* CreateBox(QString name, glm::vec3 size, glm::vec3 subdivisions);
//
//	/**
//	  * \brief Creates cylinder model.
//	  *
//	  * Creates and adds cylinder model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @param radius Radius of the cylinder model.
//	  * @param height Height of cylinder model.
//	  * @param subdivisionsAxis Defines how many angles have base of the cylinder.
//	  * @param subdivisionsHeight Number of subdivisions at the side of cylinder.
//	  * @return Created Model.
//	  */
//	Model* CreateCylinder(QString name, float radius = 1.0f, float height = 2.0f, int subdivisionsAxis = 20, int subdivisionsHeight = 1);
//
//	/**
//	  * \brief Creates cone model.
//	  *
//	  * Creates and adds cone model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @param radius Radius of the cone model.
//	  * @param height Height of cone model.
//	  * @param subdivisionsAxis Defines how many angles have base of the cone.
//	  * @param subdivisionsHeight Number of subdivisions at the side of cone.
//	  * @return Created Model.
//	*/
//	Model* CreateCone(QString name, float radius = 1.0f, float height = 2.0f, int subdivisionsAxis = 20, int subdivisionsHeight = 1);
//
//	/**
//	  * \brief Creates sphere model.
//	  *
//	  * Creates and adds sphere model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @param radius Radius of the sphere model.
//	  * @param subdivisionsAxis Defines how many meridian divisions sphere model has.
//	  * @param subdivisionsHeight Defines how many parallel divisions sphere model has.
//	  * @return Created Model.
//	  */
//	Model* CreateSphere(QString name, float radius = 1.0f, int subdivisionsAxis = 20, int subdivisionsHeight = 20);
//
//	/**
//	  * \brief Creates torus model.
//	  *
//	  * Creates and adds torus model to ModelManager.
//	  * @param name Name of the model to be set.
//	  * @param radius Radius of the torus model.
//	  * @param segmentRadius Radius of the profile of the torus.
//	  * @param subdivisionsAxis Defines how round profile of torus is.
//	  * @param subdivisionsHeight Defines how round the torus is.
//	  * @return Created Model.
//	  */
//	Model* CreateTorus(QString name, float radius = 1.0f, float segmentRadius = 0.4f, int subdivisionsAxis = 20, int subdivisionsHeight = 20);

	/**
	  * \brief Adds support of specific importer for ModelBuilder.
	  *
	  * @param importer Importer to support.
	  */
	static void AddImporter(AbstractModelImporter* importer);

private:
	static QMap<QString, AbstractModelImporter*> supportedExtensions;
	static QMap<QString, AbstractModelBuilder*> supportedShapes;

	Model* Load(QString fileUrl);
};

