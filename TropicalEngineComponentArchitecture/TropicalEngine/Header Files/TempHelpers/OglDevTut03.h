#pragma once
#include <GL/glew.h>
#include <glm.hpp>

#include <QtCore/qobject.h>
#include <QtCore/qtime>

#include <Utills\Singleton.h>

namespace TropicalEngine
{

	class OglDevTut03 : public Singleton<OglDevTut03>// TODO: Get rid of this class.
	{
	public:
		static class Level* level;

		void InitializeLevel(class Scene* scene);
	};

}