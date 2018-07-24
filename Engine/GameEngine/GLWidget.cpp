#include "GLWidget.h"
#include "ExampleGame_\GraphicsProjects\SimpleTriangle\Header.h"

#include <QtGui\QMouseEvent>

#include <iostream>
#include <cassert>


GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	setMouseTracking(true);

	pInstance = new SimpleTriangle();
}

GLWidget::~GLWidget()
{
	if (pInstance != nullptr)
		delete pInstance;
}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();

	glEnable(GL_CULL_FACE);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	pInstance->Init();

}

void GLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	pInstance->Update();
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
//	printf("%d, %d\n", event->x(), event->y());
}
