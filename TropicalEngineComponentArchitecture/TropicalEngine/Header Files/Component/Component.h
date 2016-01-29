#pragma once
#include <QtCore/qhash.h>

#include <Serialization/ISerializableJSON.h>

#include <Package/AssetManager.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Abstract Component class.
	  */
	#pragma endregion
	class Component : public ISerializableJSON
	{
	public:
		friend class Entity;

		#pragma region documentation
		/**
		  * \brief Constructor of Component Class
		  *
		  * @param owner Entity object the component will be attached to.
		  */
		#pragma endregion
		Component(class Entity* owner);
		#pragma region documentation
		/**
		  * \brief Destructor of Component.
		  */
		#pragma endregion
		~Component(void);

		#pragma region documentation
		/**
		  * \brief Gets pointer to Entity object the Component is attached to.
		  *
		  * @return Pointer to Entity object the Component is attached to
		  */
		#pragma endregion
		class Entity* getOwner()	{ return owner; }
		#pragma region documentation
		/**
		  * \brief Attaches Component to Entity object.
		  *
		  * Detaches Component from previous Entity and attaches to the new one.
		  * @param owner Pointer to Entity object the Component will be attached to.
		  */
		#pragma endregion
		void setOwner(class Entity* owner);

		#pragma region documentation
		/**
		  * \brief Gets pointer to Level this Component belongs to.
		  *
		  * @return Pointer to Level this Component belongs to.
		  */
		#pragma endregion
		class Level* getLevel();
		#pragma region documentation
		/**
		  * \brief Defines what Component is supposed to do when owning Entity changes Level it belongs to.
		  */
		#pragma endregion
		virtual void levelChanged()	{}

		#pragma region Component types metadata handling
		static bool isComponentTypeUsed(QString name);
		static unsigned int getComponentType(QString name);

		static unsigned int getParameterType(QString name);

		static QHash<QString, QString> getParameters(QString componentTypeName);	//if so change here as well
		#pragma endregion

		#pragma region documentation
		/**
		  * \brief Serializes Component to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * /brief Deserializes Component from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Component object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		// TODO: Figure out if make it private?
		#pragma region documentation
		/**
		  * \brief Entity owning this Component.
		  */
		#pragma endregion
		class Entity* owner;

		#pragma region documentation
		/**
		  * /brief Simple Constructor used to create Component instance while serializing.
		  */
		#pragma endregion
		Component();

		#pragma region documentation
		/**
		  * /brief Detaches Component from owning Entity object.
		  *
		  * Detaches Component from owning Entity object. Results in Component flying loosely unattached to anything.
		  */
		#pragma endregion
		void Detach();

		#pragma region Component types metadata handling
		virtual void InitializeComponentType() = 0;
		void AddComponentType(QString name);

		static QString getParrentType(QString componentTypeName);
		void SetParrentComponentType(QString parrentTypeName);

		void AddParameter(QString name, QString type);
		#pragma endregion
	private:
		static QHash<QString, unsigned int> componentTypeMap;
		static QHash<QString, QString> parrentComponentTypeMap;

		static QHash<QString, unsigned int> parameterTypeMap;
		static void AddParameterType(QString name);

		static QHash<QString, QHash<QString, QString>> parameters;	//maybe instead of last QString use unsigned int


		/*******************************
		 * TEMPORARY SOLUTION
		 *******************************/
		static QHash<QString, Component*> componentHandles;
	};

}