#pragma once
#include "Material.h"
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>

class MaterialManager
{
public:
	friend class Texture;
	friend class TextureManager;
	friend class Material;
private:
	QMap<QString, Material*> materials;

public:
	MaterialManager(void);
	~MaterialManager(void);

	void Load(Shader* shader, void* params, QString name);	//temporal declaration

	void UseMaterial(QString name);
	void UseMaterial(Material* material);
private:
	void FlushMaterial(QString name, bool forced = false);
};

