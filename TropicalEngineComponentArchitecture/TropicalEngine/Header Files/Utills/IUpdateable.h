#pragma once

namespace TropicalEngine
{

	class IUpdateable
	{
	public:
		IUpdateable(int priority = 0);
		~IUpdateable();

		virtual void OnUpdate(int deltaTime) = 0;
	};

}