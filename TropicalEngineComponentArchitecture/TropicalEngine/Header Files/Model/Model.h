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

	#pragma region documentation
	/**
	  * \brief MeshEntry is a submesh data for a Model object.
	  */
	#pragma endregion
	class MeshEntry
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		MeshEntry();
		#pragma region documentation
		/**
		  * Default destructor.
		  */
		#pragma endregion
		~MeshEntry();

		#pragma region documentation
		/**
		  * \brief GPU address of vertices VBO.
		  */
		#pragma endregion
		GLuint vertexVBO;
		#pragma region documentation
		/**
		  * \brief GPU address of normals VBO.
		  */
		#pragma endregion
		GLuint normalVBO;
		#pragma region documentation
		/**
		  * \brief GPU address of tangents VBO.
		  */
		#pragma endregion
		GLuint tangentVBO;
		#pragma region documentation
		/**
		  * \brief GPU address of bitangents VBO.
		  */
		#pragma endregion
		GLuint bitangentVBO;
		#pragma region documentation
		/**
		  * \brief GPU address of texture coordinates VBO.
		  */
		#pragma endregion
		GLuint texcoordVBO;

		#pragma region documentation
		/**
		  * \brief Number of vertices.
		  */
		#pragma endregion
		GLuint NumVertex;

		GLuint MaterialIndex;

		// TODO: Make finalization supporting flexible sets of arrays for MeshEntry.
		#pragma region documentation
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
		#pragma endregion
		void Finalize(QVector<glm::vec4>& vertices,
			QVector<glm::vec3>& normals,
			QVector<glm::vec3>& tangents,
			QVector<glm::vec3>& bitangents,
			QVector<glm::vec2>& texCoords);
	private:
		bool isFinalized = false;
	};

	#pragma region documentation
	/**
	  * \brief Class containing information about Model asset.
	  */
	#pragma endregion
	class Model : public ISerializableJSON
	{
	public:
		TYPENAME(Model)

		#pragma region documentation
		/**
		  * \brief Name of the type of model.
		  */
		#pragma endregion
		QString type;

		QVariantMap parameters;

		#pragma region documentation
		/**
		  * \brief Gets the name of the Model.
		  *
		  * @return Name of the Model.
		  */
		#pragma endregion
		QString getName();
		#pragma region documentation
		/**
		  * \brief Sets the name of the Model.
		  *
		  * @param name Name to be set for Model.
		  */
		#pragma endregion
		void setName(QString name);

		#pragma region documentation
		/**
		  * \brief Constructor for Model.
		  *
		  * @param name Name of the Model.
		  */
		#pragma endregion
		Model(QString name);
		#pragma region documentation
		/*
		 * \brief Constructor for Model.
		 *
		 * @param name Name of the Model.
		 * @param fileUrl Address of the file to load Model from.
		 */
		#pragma endregion
		Model(QString name, QString fileUrl);
		#pragma region documentation
		/**
		 * \brief Destructor of the Model.
		 */
		#pragma endregion
		~Model(void);

		#pragma region documentation
		/**
		  * \brief Submeshes of this Model.
		  */
		#pragma endregion
		QList<MeshEntry*> meshes;

		GLuint materialCount;

		#pragma region documentation
		/**
		  * \brief Serializes Model to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes Model from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Model object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;
	protected:
		//QMap<QString, QPair<typename, void*>> parameters;
	private:
		QString name;
		QString fileUrl;
	};

}