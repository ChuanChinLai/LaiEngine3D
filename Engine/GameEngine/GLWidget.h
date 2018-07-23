#pragma once

#include <QtWidgets\QOpenGLWidget>
#include <QtGui\QOpenGLFunctions> 

#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>
#include <QtGui\QOpenGLShaderProgram>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

//	Q_OBJECT // must include this if you use Qt signals/slots

public:

	GLWidget(QWidget *parent = NULL);
	~GLWidget();

protected:

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	
	void destroy();
private:

	// OpenGL State Information
	QOpenGLVertexArrayObject * m_object;
	QOpenGLShaderProgram *m_program;

	QOpenGLBuffer* m_vertex;
	QOpenGLBuffer* m_index;
};
