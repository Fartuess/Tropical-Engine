#include <Rendering/RenderingManager.h>
#include <Rendering/IRenderable.h>

#include <Scene/Scene.h>
#include <Scene/Level.h>

#include <Camera/CameraComponent.h>

#include <Texture/RenderTexture.h>

#include <TropicalEngineApplication.h>

namespace TropicalEngine
{
	RenderingManager::RenderingManager()
	{
		screenTexture = new RenderTexture("Screen Color Pass", 1024, 1024);
	}

	void RenderingManager::addRenderableObject(IRenderable* renderableObject, Level* level, QString shaderPass)
	{
		renderableObjects[level][shaderPass].append(renderableObject);
	}

	void RenderingManager::removeRenderableObject(IRenderable* renderableObject, Level* level)
	{
		for (QString shaderPass : renderableObjects[level].keys())
		{
			renderableObjects[level][shaderPass].removeAll(renderableObject);
		}
	}

	void RenderingManager::removeRenderableObject(IRenderable* renderableObject, QString shaderPass)
	{
		for (Level* level : renderableObjects.keys())
		{
			if (renderableObjects[level].contains(shaderPass))
			{
				renderableObjects[level][shaderPass].removeAll(renderableObject);
			}
		}
	}

	void RenderingManager::removeRenderableObject(IRenderable* renderableObject)
	{
		for (Level* level : renderableObjects.keys())
		{
			for (QString shaderPass : renderableObjects[level].keys())
			{
				renderableObjects[level][shaderPass].removeAll(renderableObject);
			}
		}
	}

	void RenderingManager::DrawAll(Scene* scene, QString shaderPass)
	{
		for (Level* level : scene->getLevels())
		{
			for (IRenderable* renderableObject : renderableObjects[level][shaderPass])
			{
				renderableObject->Draw(scene->getCurrentCamera(), shaderPass);
			}
		}
	}

	void RenderingManager::DrawAll(Scene* scene)
	{
		DrawAll(scene, "Shadowmap");
		screenTexture->BindFramebuffer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawAll(scene, "Default");
		DrawAll(scene, "Color");
		RenderTexture::BindDefaultFramebuffer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawAll(scene, "PostProcess");
	}

}