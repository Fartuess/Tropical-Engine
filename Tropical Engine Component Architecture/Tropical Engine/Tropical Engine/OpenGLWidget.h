#pragma once
#include <QtWidgets\qwidget.h>
#include <QtOpenGL\QGLWidget>
class OpenGLWidget : public QGLWidget
{
public:
	OpenGLWidget(void);
	~OpenGLWidget(void);
protected:
	void initializeGL();
	void resizeGL();
	void paintGL();
};

