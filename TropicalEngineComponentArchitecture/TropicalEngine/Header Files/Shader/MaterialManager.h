#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

#include "Material.h"

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
	void Load(class Shader* shader, void* params, QString name);	//temporal declaration

	void UseMaterial(QString name);
	void UseMaterial(Material* material);

private:
	QMap<QString, Material*> materials;

	void FlushMaterial(QString name, bool forced = false);
};

