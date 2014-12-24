#include <gl\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <QtGui\qkeyevent>
#include <QtGui\qmouseevent>
#include <QtCore\qdebug.h>
#include "Entity.h"
#include "CameraComponent.h"
#include "InputController.h"
#include "SceneManager.h"
#include "OglDevTut03.h"
#include "OpenGLWidget.h"

#include <QtWidgets\qapplication.h>
#include <QtCore\qthread.h>
#include "TropicalEngineApplication.h"

OpenGLWidget::OpenGLWidget(void)
{
	//setWindowFlags(Qt::
}

OpenGLWidget::~OpenGLWidget(void)
{
}

void OpenGLWidget::initializeGL()
{
	glewInit();

	connect(this, SIGNAL(initializeSignal()), TropicalEngineApplication::instance(), SLOT(Initialize()));
	//connect(this, SIGNAL(reshapeSignal()), staticOglDevTut03, SLOT(reshapeSlot()));
	connect(this, SIGNAL(drawSignal()), TropicalEngineApplication::instance(), SLOT(Draw()));

	glViewport(0, 0, 1024, 1024);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	emit initializeSignal();
}

void OpenGLWidget::resizeGL(int width, int height)
{
	if(TropicalEngineApplication::instance()->sceneManager->getCurrentCamera() != nullptr)
		TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->setAspectRatio((GLfloat)width / (GLfloat)height);
	glViewport(0, 0, width, height);
	emit reshapeSignal(width, height);
}

void OpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	emit drawSignal();

	this->update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent* keyEvent)
{
	glm::vec3 front = TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.getFront();
	glm::vec3 right = TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.getRight();
	switch ( keyEvent->key() ) {
		case Qt::Key_W:
			//qDebug("W pressed");
			TropicalEngineApplication::instance()->inputController->pressedKeys.W = true;
			TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.LocalTranslate(front * (0.1f));
			break;
		case Qt::Key_S:
			//qDebug("S pressed");
			TropicalEngineApplication::instance()->inputController->pressedKeys.S = true;
			TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.LocalTranslate(front * (-0.1f));
			break;
		case Qt::Key_A:
			//qDebug("A pressed");
			TropicalEngineApplication::instance()->inputController->pressedKeys.A = true;
			TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.LocalTranslate(right * (-0.1f));
			break;
		case Qt::Key_D:
			//qDebug("D pressed");
			TropicalEngineApplication::instance()->inputController->pressedKeys.D = true;
			TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.LocalTranslate(right * (0.1f));
			break;
		case Qt::Key_Space:
			//qDebug("Space pressed");
			TropicalEngineApplication::instance()->inputController->pressedKeys.D = true;
			TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.LocalTranslate(glm::vec3(0.0f, 0.1f, 0.0f));
			break;
		case Qt::Key_C:
			//qDebug("C pressed");
			TropicalEngineApplication::instance()->inputController->pressedKeys.D = true;
			TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.LocalTranslate(glm::vec3(0.0f, -0.1f, 0.0f));
			break;
		}
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
{
	//qDebug() << "X: " << mouseEvent->globalX() << " Y: " << mouseEvent->globalY();
	TropicalEngineApplication::instance()->inputController->mousePosition = glm::vec2(mouseEvent->globalX(), mouseEvent->globalY());

	glm::quat quat1 = glm::angleAxis(mouseEvent->globalX() / 6.0f, glm::vec3(0.0f, -1.0f, 0.0f));
	TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.setLocalRotation(quat1);
	glm::quat quat2 = glm::angleAxis(mouseEvent->globalY() / 6.0f - 90.0f, TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.getRight());
	//qDebug() << "X: " << mouseEvent->globalY() / 6.0f - 90.0f;
	TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->getOwner()->transform.setLocalRotation(quat2 * quat1);
}
