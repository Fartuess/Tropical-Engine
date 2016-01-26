#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include "Material.h"

namespace TropicalEngine
{

	class MaterialManager
	{
	public:
		friend class Texture;
		friend class TextureManager;
		friend class Material;

		MaterialManager(void);
		~MaterialManager(void);

		Material* operator[](QString name)	{ return materials[name]; };
		const Material* operator[](QString name) const	{ return materials[name]; };

		///TODO: Rethink Load method.
		Material* Load(class Shader* shader, QString name);	//temporal declaration

		void UseMaterial(QString name);
		void UseMaterial(Material* material);

	private:
		QHash<QString, Material*> materials;	/// TODO: Figure out if QHash or QMap. In some border cases materials might be created every frame.

		void FlushMaterial(QString name, bool forced = false);
	};

}