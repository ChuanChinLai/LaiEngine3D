#include "GLWidget.h"
#include "Window.h"
#include "MainWindow.h"

#include <QtWidgets\QGridLayout>
#include <QtWidgets\QPushButton>
#include <QtGui\QMouseEvent>

#include <iostream>

Window::Window(MainWindow* parent) : pMainWindow(parent)
{
	pGLWidget = new GLWidget(this);

	QGridLayout* pLayout = new QGridLayout(this);
	pLayout->addWidget(pGLWidget, 0, 0);

	QPushButton* button = new QPushButton(this);
	pLayout->addWidget(button, 2, 0);

	setLayout(pLayout);
}

void Window::keyPressEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		pMainWindow->close();
		break;
	default:
		std::cout << event->key() << std::endl;
		break;
	}
}
