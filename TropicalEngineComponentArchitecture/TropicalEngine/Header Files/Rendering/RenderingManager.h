#pragma once
#include <QtCore/qhash.h>
#include <QtCore/qlist.h>
#include <QtCore/qstring.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing rendering and renderable objects.
	  */
	#pragma endregion
	class RenderingManager : public Singleton<RenderingManager>
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		RenderingManager();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~RenderingManager()	{}

		//temp
		void setScreenSize(int width, int height);

		#pragma region documentation
		/**
		  * \brief Adds renderable object into the manager.
		  *
		  * @param renderableObject Object to add.
		  * @param level To which level adds the object.
		  * @param shaderPass Name of shaderPass to use.
		  */
		#pragma endregion
		void addRenderableObject(class IRenderable* renderableObject, class Level* level, QString shaderPass = "Default");
		#pragma region documentation
		/**
		  * \brief Removes renderable object from specific level.
		  *
		  * @param renderableObject Object to remove.
		  * @param level Level to remove from.
		  */
		#pragma endregion
		void removeRenderableObject(class IRenderable* renderableObject, class Level* level);
		#pragma region documentation
		/**
		  * \brief Removes renderable object from shader pass.
		  *
		  * @param renderableObject Object to remove.
		  * @param shaderPass Name of shader pass to remove from.
		  */
		#pragma endregion
		void removeRenderableObject(class IRenderable* renderableObject, QString shaderPass);
		#pragma region documentation
		/**
		  * \brief Removes renderable object from manager.
		  *
		  * @param renderableObject Object to remove.
		  */
		#pragma endregion
		void removeRenderableObject(class IRenderable* renderableObject);
		#pragma region documentation
		/**
		  * \brief Draws the selected shader pass of Scene.
		  *
		  * @param scene Scene to draw.
		  * @param shaderPass Name of shader pass to render.
		  */
		#pragma endregion
		void DrawAll(class Scene* scene, QString shaderPass);
		#pragma region documentation
		/**
		  * \brief Draws Scene.
		  *
		  * Used shader passes and order of invoking them is definied inside of this method.
		  * @param scene Scene to draw.
		  */
		#pragma endregion
		void DrawAll(class Scene* scene);

	protected:
		QHash<class Level*, QHash<QString, QList<class IRenderable*>>> renderableObjects;

	private:
		int screenWidth;	//temp?
		int screenHeight;	//temp?
		class RenderTexture* screenTexture;
	};

}