#pragma once

#include"Shaders_header.h"
#include<GL\glus.h>

Shader::Shader(string VSpath, string PSpath)
{
	GLUStextfile VSsource;
	GLUStextfile PSsource;

	glusLoadTextFile(&VSpath[0] , &VSsource);
	glusLoadTextFile(&PSpath[0] , &PSsource);

	glusBuildProgramFromSource(&shaderProgram, (const GLUSchar**) &VSsource.text, 0, 0, 0, (const GLUSchar**) &PSsource.text);

	glusDestroyTextFile(&VSsource);
	glusDestroyTextFile(&PSsource);
}

GLUSuint Shader::getProgram()
{
	return shaderProgram.program;
}