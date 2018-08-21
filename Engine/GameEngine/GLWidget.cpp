#include "GLWidget.h"
#include "ExampleGame_\GraphicsProjects\SimpleTriangle\Header.h"

#include <QtGui\QMouseEvent>
#include <QtCore\Qtimer>
#include <iostream>
#include <cassert>


GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	setMouseTracking(true);

	m_pInstance = new LaiEngine::SimpleTriangle(this);
}

GLWidget::~GLWidget()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	
	glEnable(GL_CULL_FACE);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	m_pInstance->Init();
}

void GLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_pInstance->Update();
}


void GLWidget::keyPressEvent(QKeyEvent * event)
{
	if (m_pInstance->KeyPressEvent(event))
	{
		update();
	}
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	m_pInstance->MouseMoveEvent(event);
}
