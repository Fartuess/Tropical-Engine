#pragma once
#include <QtWidgets\qapplication.h>
#include <QtCore\qtime>
#include <QtCore\qsettings.h>

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

class CameraComponent;

class OglDevTut03;

class SceneGraphWidget;

class GuiStyleManager;

class TropicalEngineApplication : public QApplication
{
	Q_OBJECT
private:
	/*
	 * Delta time.
	 */
	int deltaTime;
	QTime deltaTimer;
public:
	/*
	* Resource management
	*/
	ShaderManager* shaderManager;
	MaterialManager* materialManager;
	TextureManager* textureManager;
	ModelManager* modelManager;
	ModelBuilder* modelBuilder;
	PackageManager* packageManager;
	/*
	* Scene controlling
	*/
	SceneManager* sceneManager;
	ModelController* modelController;
	LightController* lightController;
	/*
	* Input
	*/
	InputController* inputController;

	OglDevTut03* renderer;	//temporarily
	/*
	* Gui
	*/
	GuiStyleManager* styleManager;
	SceneGraphWidget* sceneGraph;
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
};

