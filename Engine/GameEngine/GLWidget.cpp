#include "GLWidget.h"

#include <QtGui\QMouseEvent>
#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>
#include <QtGui\QOpenGLShaderProgram>

#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	setMouseTracking(true);
}

void GLWidget::initializeGL()
{
	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_COLOR_MATERIAL);
	//glEnable(GL_BLEND);
	//glEnable(GL_POLYGON_SMOOTH);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initializeOpenGLFunctions();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	QOpenGLShaderProgram s;
	glBegin(GL_POLYGON);
	
	glColor3f(1, 0, 0);
	glVertex3f(0, 1.0f, 0);

	glColor3f(0, 1, 0);
	glVertex3f(1.0f, -1.0f, 0);

	glColor3f(0, 0, 1);
	glVertex3f(-1.0f, -1.0f, 0);

	glEnd();
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	printf("%d, %d\n", event->x(), event->y());
}