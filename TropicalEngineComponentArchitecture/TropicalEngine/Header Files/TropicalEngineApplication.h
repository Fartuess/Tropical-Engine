#pragma once
#include <QtCore/qtime>
#include <QtCore/qsettings.h>
#include <QtWidgets/qapplication.h>

class TropicalEngineApplication : public QApplication
{
	Q_OBJECT
public:
	/*
	* Resource management
	*/
	class ShaderManager* shaderManager;
	class MaterialManager* materialManager;
	class TextureManager* textureManager;
	class ModelManager* modelManager;
	class ModelBuilder* modelBuilder;
	class PackageManager* packageManager;
	/*
	* Scene controlling
	*/
	class SceneManager* sceneManager;
	class ModelController* modelController;
	class LightController* lightController;
	/*
	* Input
	*/
	class InputManager* inputManager;

	class OglDevTut03* renderer;	//temporarily
	/*
	* Gui
	*/
	class GuiStyleManager* styleManager;
	class SceneGraphWidget* sceneGraph;
	/*
	* Settings
	*/
	QSettings* EngineSettings;
	QSettings* EditorSettings;

	TropicalEngineApplication(int argc, char* argv[]);
	~TropicalEngineApplication(void);

	static TropicalEngineApplication* instance();
public slots:
	void Initialize();
	void Draw();
private:
	/*
	* Delta time.
	*/
	int deltaTime;
	QTime deltaTimer;
};

