#pragma once
#include <QtCore/qset.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing Scenes.
	  */
	#pragma endregion
	class SceneManager
	{
	public:
		friend class Scene;

		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		SceneManager()	{};
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~SceneManager()	{};

	protected:
		#pragma region documentation
		/**
		  * \brief Set of Scenes currently in engine.
		  */
		#pragma endregion
		QSet<class Scene*> scenes;
	};

}