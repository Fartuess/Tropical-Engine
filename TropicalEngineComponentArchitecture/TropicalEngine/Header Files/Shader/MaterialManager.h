#pragma once
#include "Shader/Material.h"
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

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

