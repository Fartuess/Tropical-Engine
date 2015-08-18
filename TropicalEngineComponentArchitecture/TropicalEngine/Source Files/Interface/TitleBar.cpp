#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/qlabel.h>
#include <QtGui/qevent.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qdesktopwidget.h>

#include <QtCore/qdebug.h>

#include <Interface/TitleBar.h>


TitleBar::TitleBar(QWidget* rootParent, QWidget* parent) : QWidget(parent)
{
	this->rootParent = rootParent;

	QHBoxLayout* TitleBarLayout = new QHBoxLayout();
	QSizePolicy* expandVertically = new QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	setSizePolicy(*expandVertically);

	QLabel* Title = new QLabel("Tropical Engine");
	Title->setObjectName("Title");
	QPushButton* minimize = new QPushButton("-");
	QPushButton* maximize = new QPushButton("O");
	QPushButton* close = new QPushButton("X");
	maximize->setCheckable(true);

	TitleBarLayout->addWidget(Title);
	TitleBarLayout->addStretch();
	TitleBarLayout->addWidget(minimize);
	TitleBarLayout->addWidget(maximize);
	TitleBarLayout->addWidget(close);

	setLayout(TitleBarLayout);

	connect(maximize, SIGNAL(clicked()), this, SLOT(toggleMaximize()));
	connect(minimize, SIGNAL(clicked()), rootParent, SLOT(showMinimized()));
	connect(close, SIGNAL(clicked()), rootParent, SLOT(close()));
}

TitleBar::~TitleBar()
{
}

void TitleBar::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		isGrabbed = true;
		if (!isMaximized && !isSided)
		{
			previousPosition = rootParent->pos();
		}
		mousePositionOffset = rootParent->pos() - e->globalPos();
	}
}

void TitleBar::mouseReleaseEvent(QMouseEvent* e)
{
	if (isGrabbed = true)
	{
		if (e->globalY() == 0)
		{
			if (!isSided)
			{
				previousSize = rootParent->size();
			}
			isMaximized = true;
			isSided = false;
			rootParent->showMaximized();
		}
		else
		{
			///TODO: Sided window should not go under start bar.
			QRect screenRect = QApplication::desktop()->screenGeometry();
			if (e->globalX() == screenRect.left())
			{
				if (!isSided)
				{
					previousSize = rootParent->size();
				}
				rootParent->resize(screenRect.width() / 2, screenRect.height());
				rootParent->move(screenRect.topLeft());
				isSided = true;
			}
			if (e->globalX() == screenRect.right())
			{
				if (!isSided)
				{
					previousSize = rootParent->size();
				}
				rootParent->resize(screenRect.width() / 2, screenRect.height());
				rootParent->move(QPoint(screenRect.center().x(), 0));
				isSided = true;
			}
		}
	}
	isGrabbed = false;
}

void TitleBar::mouseMoveEvent(QMouseEvent* e)
{
	if (isGrabbed)
	{
		if (isMaximized || isSided)
		{
			QRect windowRect = rootParent->rect();
			if (!(qAbs(e->globalPos().x() - windowRect.left()) < previousSize.width() / 2))
			{
				if (qAbs(e->globalPos().x() - windowRect.right()) < previousSize.width() / 2)
				{
					mousePositionOffset.setX(-(previousSize.width() - qAbs(windowRect.right() - (e->globalPos().x()))));
				}
				else
				{
					mousePositionOffset.setX(-previousSize.width() / 2);
				}
			}
			rootParent->showNormal();
			rootParent->resize(previousSize);
			isMaximized = false;
			isSided = false;
		}
		rootParent->move(e->globalPos() + mousePositionOffset);
	}
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* e)
{
	if (isMaximized || isSided)
	{
		isMaximized = false;
		isSided = false;
		rootParent->showNormal();
		rootParent->resize(previousSize);
		rootParent->move(previousPosition);
	}
	else
	{
		previousSize = rootParent->size();
		previousPosition = rootParent->pos();
		isMaximized = true;
		isSided = false;
		rootParent->showMaximized();
	}
}

void TitleBar::toggleMaximize()
{
	if (isMaximized)
	{
		isMaximized = false;
		rootParent->showNormal();
		rootParent->resize(previousSize);
		rootParent->move(previousPosition);
	}
	else
	{
		if (!isSided)
		{
			previousSize = rootParent->size();
			previousPosition = rootParent->pos();
		}
		isMaximized = true;
		isSided = false;
		rootParent->showMaximized();
	}
}