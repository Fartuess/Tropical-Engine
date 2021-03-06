#pragma once
#include <glm.hpp>

#include <Component\Component.h>
#include <Utills\IUpdateable.h>

namespace TropicalEngine
{

	class TempMovingComponent :
		public Component,
		public IUpdateable
	{
	public:
		TYPENAME(TempMovingComponent)

		TempMovingComponent(Entity* owner, glm::vec3 startPos, glm::vec3 endPos, float timespan);
		~TempMovingComponent();

		virtual void OnUpdate(int deltaTime) override;
	protected:
		void InitializeComponentType() override;
	private:
		glm::vec3 half;
		glm::vec3 variance;
		float timespan;
		float currentTime;;
	};

}