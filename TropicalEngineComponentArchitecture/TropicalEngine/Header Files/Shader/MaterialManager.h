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

	///TODO: Rethink Load method.
	void Load(Shader* shader, void* params, QString name);	//temporal declaration

	void UseMaterial(QString name);
	void UseMaterial(Material* material);

private:
	QMap<QString, Material*> materials;

	void FlushMaterial(QString name, bool forced = false);
};

