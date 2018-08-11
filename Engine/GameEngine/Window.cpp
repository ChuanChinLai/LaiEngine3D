#include "GLWidget.h"
#include "Window.h"
#include "MainWindow.h"
#include "InspectorWindow.h"

#include <QtWidgets\QGridLayout>
#include <QtWidgets\QPushButton>
#include <QtGui\QMouseEvent>

#include <iostream>

Window::Window(MainWindow* parent) : m_pMainWindow(parent)
{
	QHBoxLayout* mainLayout = new QHBoxLayout(this);

	m_pGLWidget = new GLWidget(this);
	mainLayout->addWidget(m_pGLWidget);

	InspectorWindow* m_pGLWidget1 = new InspectorWindow(this);
	mainLayout->addWidget(m_pGLWidget1);

	setLayout(mainLayout);
}

void Window::keyPressEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		m_pMainWindow->close();
		break;
	default:
		m_pGLWidget->keyPressEvent(event);
		break;
	}
}
