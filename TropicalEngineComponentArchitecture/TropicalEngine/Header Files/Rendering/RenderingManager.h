#pragma once

#include <QtCore/qhash.h>
#include <QtCore/qlist.h>
#include <QtCore/qstring.h>

namespace TropicalEngine
{

	class RenderingManager
	{
	public:
		RenderingManager();
		~RenderingManager();

		void addRenderableObject(class IRenderable* renderableObject, class Level* level, QString shaderPass = "color");
		void removeRenderableObject(class IRenderable* renderableObject, class Level* level);
		void removeRenderableObject(class IRenderable* renderableObject, QString shaderPass);
		void removeRenderableObject(class IRenderable* renderableObject);

		void DrawAll(class Scene* scene, QString shaderPass);
		void DrawAll(class Scene* scene);

	protected:
		QHash<class Level*, QHash<QString, QList<class IRenderable*>>> renderableObjects;
	};

}