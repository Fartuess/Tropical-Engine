#pragma once
#include <QtCore/qhash.h>

#include <Serialization/ISerializableJSON.h>

#include <Package/AssetManager.h>

namespace TropicalEngine
{

	class Entity;

	/**
	  * Abstract Component class.
	  */
	class Component : public ISerializableJSON
	{
	public:
		friend class Entity;

		/**
		  * \brief Constructor of Component Class
		  *
		  * @param owner Entity object the component will be attached to.
		  */
		Component(Entity* owner);

		/**
		  * \brief Destructor of Component.
		  */
		~Component(void);

		/**
		  * \brief Gets pointer to Entity object the Component is attached to.
		  *
		  * @return Pointer to Entity object the Component is attached to
		  */
		Entity* getOwner()	{ return owner; }

		/**
		  * \brief Attaches Component to Entity object.
		  *
		  * Detaches Component from previous Entity and attaches to the new one.
		  * @param owner Pointer to Entity object the Component will be attached to.
		  */
		void setOwner(Entity* owner);

		class Level* getLevel();
		virtual void levelChanged()	{}

		static bool isComponentTypeUsed(QString name);
		static unsigned int getComponentType(QString name);

		static unsigned int getParameterType(QString name);

		static QHash<QString, QString> getParameters(QString componentTypeName);	//if so change here as well

		/**
		  * \brief Serializes Component to JSON object.
		  *
		  * @return Result of serialization.
		  */
		QJsonObject toJSON() override;

		/**
		  * /brief Deserializes Component from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Component object.
		  */
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		///TODO: Make it private?
		/**
		  * \brief Entity owning this Component.
		  */
		Entity* owner;

		/**
		  * /brief Simple Constructor used to create Component instance while serializing.
		  */
		Component();

		/**
		  * /brief Detaches Component from owning Entity object.
		  *
		  * Detaches Component from owning Entity object. Results in Component flying loosely unattached to anything.
		  */
		void Detach();

		virtual void InitializeComponentType() = 0;
		void AddComponentType(QString name);

		static QString getParrentType(QString componentTypeName);
		void SetParrentComponentType(QString parrentTypeName);

		void AddParameter(QString name, QString type);

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