#include <gl/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <QtCore/qdebug.h>
#include <QtCore/qthread.h>
#include <QtGui/qkeyevent>
#include <QtGui/qmouseevent>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qdesktopwidget.h>

#include <Scene/Entity.h>
#include <Scene/Scene.h>

#include <Rendering/RenderingManager.h>

#include <Camera/CameraComponent.h>
#include <Input/InputManager.h>
#include <TempHelpers/OglDevTut03.h>
#include <Interface/OpenGLWidget.h>

#include <Texture/RenderTexture.h>

#include <TropicalEngineApplication.h>

namespace TropicalEngine
{

	OpenGLWidget::OpenGLWidget(void)
	{
		screenCenter = new QPoint(QApplication::desktop()->screenGeometry().center());
		abstractMousePosition = new QPoint(*screenCenter);
		mouseGrabPoint = new QPoint(0, 0);
	}

	OpenGLWidget::OpenGLWidget(Scene* scene) : OpenGLWidget()
	{
		setScene(scene);
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
		//glFrontFace(GL_CCW);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		//widgetFramebuffer = new RenderTexture("Viewport_color", 1024, 1024);
		//widgetFramebuffer->BindFramebuffer();
		//RenderTexture::BindDefaultFramebuffer();

		emit initializeSignal();
	}

	void OpenGLWidget::resizeGL(int width, int height)
	{
		if (drawnScene->getCurrentCamera() != nullptr)
			drawnScene->getCurrentCamera()->setAspectRatio((GLfloat)width / (GLfloat)height);
		glViewport(0, 0, width, height);
		RenderingManager::instance().setScreenSize(width, height);

		//emit reshapeSignal(width, height);
		//this->update();
	}

	void OpenGLWidget::paintGL()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		emit drawSignal();

		this->update();
	}

	void OpenGLWidget::keyPressEvent(QKeyEvent* keyEvent)
	{
		InputManager::instance().PressKey(keyEvent->key());
	}

	void OpenGLWidget::keyReleaseEvent(QKeyEvent* keyEvent)
	{
		InputManager::instance().ReleaseKey(keyEvent->key());
	}

	void OpenGLWidget::mousePressEvent(QMouseEvent* mouseEvent)
	{
		if (!isMousePressed)
		{
			*mouseGrabPoint = mouseEvent->globalPos();
			previousCursor = new QCursor(cursor());
			this->setCursor(Qt::BlankCursor);
			QCursor::setPos(*screenCenter);
		}
		isMousePressed++;
	}

	void OpenGLWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
	{
		if (isMousePressed == 1)
		{
			QCursor::setPos(*mouseGrabPoint);
			this->setCursor(*previousCursor);
			delete previousCursor;
		}
		isMousePressed--;
	}

	void OpenGLWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
	{
		*abstractMousePosition += mouseEvent->globalPos() - *screenCenter;

		InputManager::instance().mousePosition = glm::vec2(abstractMousePosition->x(), abstractMousePosition->y());

		glm::quat quat1 = glm::angleAxis(abstractMousePosition->x() / 6.0f, glm::vec3(0.0f, -1.0f, 0.0f));
		drawnScene->getCurrentCamera()->getOwner()->transform.setLocalRotation(quat1);
		glm::quat quat2 = glm::angleAxis(abstractMousePosition->y() / 6.0f - 90.0f, -drawnScene->getCurrentCamera()->getOwner()->transform.getRight());

		drawnScene->getCurrentCamera()->getOwner()->transform.setLocalRotation(quat2 * quat1);

		QCursor::setPos(*screenCenter);
	}

}