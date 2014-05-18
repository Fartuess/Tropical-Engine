#pragma once
#include <QtWidgets\qwidget.h>
#include <QtOpenGL\QGLWidget>

class OglDevTut03;

class OpenGLWidget : public QGLWidget
{
private:
	OglDevTut03* GLclass;
public:
	OpenGLWidget(void);
	~OpenGLWidget(void);
protected:
	void initializeGL();
	void resizeGL();
	void paintGL();
};

