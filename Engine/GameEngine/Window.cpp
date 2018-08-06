#include "GLWidget.h"
#include "Window.h"
#include "MainWindow.h"

#include <QtWidgets\QGridLayout>
#include <QtWidgets\QPushButton>
#include <QtGui\QMouseEvent>

#include <iostream>

Window::Window(MainWindow* parent) : m_pMainWindow(parent)
{
	m_pGLWidget = new GLWidget(this);

	QGridLayout* pLayout = new QGridLayout(this);
	pLayout->addWidget(m_pGLWidget, 0, 0);

	QPushButton* pButton = new QPushButton(this);
	pLayout->addWidget(pButton, 2, 0);

	setLayout(pLayout);
}

void Window::keyPressEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		m_pMainWindow->close();
		break;
	default:
		std::cout << event->key() << std::endl;
		break;
	}
}
