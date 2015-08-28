#include <Shader/ShaderException.h>


ShaderException::ShaderException(QString message, Shader* shader) : Exception(message, shader)
{
}


ShaderException::~ShaderException()
{
}
