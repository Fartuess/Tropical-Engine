#include <gl\glew.h>
#include "OglDevTut03.h"
#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(void)
{
}


OpenGLWidget::~OpenGLWidget(void)
{
}

void OpenGLWidget::initializeGL()
{
	glewInit();
	GLclass = new OglDevTut03();
	GLclass->Initialize();
}

void OpenGLWidget::resizeGL()
{

}

void OpenGLWidget::paintGL()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	GLclass->Draw();
}