#include <gl\glew.h>
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
}

void OpenGLWidget::resizeGL()
{

}

void OpenGLWidget::paintGL()
{
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}