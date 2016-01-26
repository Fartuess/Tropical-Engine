#pragma once
#include <GL/glew.h>
#include <glm.hpp>

#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtCore/qlist.h>
#include <QtCore/qvariant.h>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	/**
	  * MeshEntry is a submesh data for a Model object.
	  */
	class MeshEntry
	{
	public:
		/**
		  * \brief Default constructor.
		  */
		MeshEntry();

		/**
		  * Default destructor.
		  */
		~MeshEntry();

		/**
		  * \brief GPU address of vertices VBO.
		  */
		GLuint vertexVBO;

		/**
		  * \brief GPU address of normals VBO.
		  */
		GLuint normalVBO;

		/**
		  * \brief GPU address of tangents VBO.
		  */
		GLuint tangentVBO;

		/**
		  * \brief GPU address of bitangents VBO.
		  */
		GLuint bitangentVBO;

		/**
		  * \brief GPU address of texture coordinates VBO.
		  */
		GLuint texcoordVBO;

		/**
		  * \brief Number of vertices.
		  */
		GLuint NumVertex;

		GLuint MaterialIndex;

		///TODO: Make finalization supporting flexible sets of arrays.
		/**
		  * \brief Finalizes creation of Mesh Entry.
		  *
		  * Sets everything on the GPU side.
		  * @param vertices Vector of vertices of the mesh.
		  * @param normals Vector of normals of the mesh.
		  * @param tangents Vector of tangents of the mesh.
		  * @param bitangents Vector of bitangents of the mesh.
		  * @param texCoords Vector of texCoords of the mesh.
		  */
		void Finalize(QVector<glm::vec4>& vertices,
			QVector<glm::vec3>& normals,
			QVector<glm::vec3>& tangents,
			QVector<glm::vec3>& bitangents,
			QVector<glm::vec2>& texCoords);
	private:
		bool isFinalized = false;
	};

	class Model : public ISerializableJSON
	{
	public:
		TYPENAME(Model)

		/**
		  * \brief Name of the type of model.
		  */
		QString type;

		QVariantMap parameters;

		/**
		  * \brief Gets the name of the Model.
		  *
		  * @return Name of the Model.
		  */
		QString getName();

		/**
		  * \brief Sets the name of the Model.
		  *
		  * @param name Name to be set for Model.
		  */
		void setName(QString name);

		/**
		  * \brief Constructor for Model.
		  *
		  * @param name Name of the Model.
		  */
		Model(QString name);

		/*
		 * \brief Constructor for Model.
		 *
		 * @param name Name of the Model.
		 * @param fileUrl Address of the file to load Model from.
		 */
		Model(QString name, QString fileUrl);

		/**
		 * \brief Destructor of the Model.
		 */
		~Model(void);

		/**
		  * \brief Submeshes of this Model.
		  */
		QList<MeshEntry*> meshes;


		GLuint materialCount;

		/**
		  * \brief Serializes Model to JSON object.
		  *
		  * @return Result of serialization.
		  */
		QJsonObject toJSON() override;

		/**
		  * \brief Deserializes Model from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Model object.
		  */
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;
	protected:
		//QMap<QString, QPair<typename, void*>> parameters;
	private:
		QString name;
		QString fileUrl;
	};

}