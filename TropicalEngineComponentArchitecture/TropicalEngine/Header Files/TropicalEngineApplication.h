#pragma once
#include <QtCore/qtime>
#include <QtCore/qsettings.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qsplashscreen.h>
#include <QtGui/qpixmap.h>

namespace TropicalEngine
{

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
		class AssetManager* assetManager;
		class PackageManager* packageManager;
		/*
		* Scene controlling
		*/
		class Scene* tempScene;
		class SceneManager* sceneManager;
		class LightController* lightController;
		/*
		 * Updatings
		 */
		class UpdateManager* updateManager;
		class RenderingManager* renderingManager;
		class OglDevTut03* renderer;	//temporarily

		/*
		* Input
		*/
		class InputManager* inputManager;

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

		QPixmap* splashImage;
		QSplashScreen* splashScreen;
	};

}