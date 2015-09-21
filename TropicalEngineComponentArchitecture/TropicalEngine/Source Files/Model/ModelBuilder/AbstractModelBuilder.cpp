#include <Utills/Exception.h>

#include <Model/Model.h>
#include <Model/ModelBuilder/AbstractModelBuilder.h>


AbstractModelBuilder::AbstractModelBuilder()
{
	modelType = "Unknown Generated";

	parameters["name"] = (void*)(new QString(""));
}


AbstractModelBuilder::~AbstractModelBuilder()
{
}

QString AbstractModelBuilder::getModelType()
{
	return modelType;
}

void AbstractModelBuilder::setParameter(QString name, void* value)
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
	parameters["name"] = (void*)(new QString(""));
}