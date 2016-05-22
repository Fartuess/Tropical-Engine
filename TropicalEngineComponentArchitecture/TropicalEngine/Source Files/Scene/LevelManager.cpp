#include <Scene/LevelManager.h>

#include <Scene/LevelImporter/AbstractLevelImporter.h>

namespace TropicalEngine
{

	QHash<QString, AbstractLevelImporter*> LevelManager::supportedExtensions = QHash<QString, AbstractLevelImporter*>();

	LevelManager::LevelManager(void)
	{
	}

	LevelManager::~LevelManager(void)
	{
		// TODO: implement it.
	}

	Level* LevelManager::LoadLevel(QString fileUrl, QString name)
	{
		Level* level = supportedExtensions[fileUrl.section(".", -1, -1).toLower()]->Load(name, fileUrl);
		levels[name] = level;

		return level;
	}

	void LevelManager::FlushLevel(QString name)
	{
		// TODO: implement it.
	}

	void LevelManager::AddImporter(AbstractLevelImporter* importer)
	{
		for (QString extensionName : importer->getSupportedExtensions())
		{
			supportedExtensions[extensionName] = importer;
		}
	}

}