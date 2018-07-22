#pragma once

#include <QtWidgets\QOpenGLWidget>
#include <QtGui\QOpenGLFunctions> 

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

//	Q_OBJECT // must include this if you use Qt signals/slots

public:

	GLWidget(QWidget *parent = NULL);

protected:

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
};
