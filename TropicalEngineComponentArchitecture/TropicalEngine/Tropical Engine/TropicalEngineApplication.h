#pragma once
#include <QtWidgets\qapplication.h>

class ShaderManager;
class MaterialManager;

class TextureManager;

class ModelManager;
class ModelController;
class ModelBuilder;

class PackageManager;
class SceneManager;
class SceneController;

class LightController;

class InputController;

class TropicalEngineApplication : public QApplication
{
public:
	ShaderManager* shaderManager;
	MaterialManager* materialManager;
	
	TextureManager* textureManager;
	
	ModelManager* modelManager;
	ModelController* modelController;
	ModelBuilder* modelBuilder;
	
	PackageManager* packageManager;
	SceneManager* sceneManager;
	SceneController* sceneController;
	
	LightController* lightController;
	
	InputController* inputController;

	TropicalEngineApplication(int argc, char* argv[]);
	~TropicalEngineApplication(void);

	static TropicalEngineApplication* instance();
};

