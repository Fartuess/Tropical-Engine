#pragma once
#include <QtCore/qlist.h>

#include "../Level.h"

namespace TropicalEngine
{

	class AbstractLevelImporter
	{
	public:
		virtual Level* Load(QString name, QString fileUrl) = 0;

		QList<QString> getSupportedExtensions();

	protected:
		QList<QString> supportedExtensions;
	};

}