#include <Utills/Exception.h>

#include <Model/Model.h>
#include <Model/ModelBuilder/AbstractModelBuilder.h>

namespace TropicalEngine
{

	AbstractModelBuilder::AbstractModelBuilder()
	{
		modelType = "Unknown Generated";

		parameters["name"] = QString("");
	}


	AbstractModelBuilder::~AbstractModelBuilder()
	{
	}

	QString AbstractModelBuilder::getModelType()
	{
		return modelType;
	}

	void AbstractModelBuilder::setParameter(QString name, QVariant value)
	{
		if (parameters.contains(name))
		{
			parameters[name] = value;
		}
		else
		{
			throw Exception<AbstractModelBuilder>("Parameter with given name does not exist!", this);
		}
	}

	void AbstractModelBuilder::resetParameters()
	{
		parameters["name"] = QString("");
	}

}