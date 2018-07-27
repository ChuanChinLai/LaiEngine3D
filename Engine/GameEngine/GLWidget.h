#pragma once

#include <QtWidgets\QOpenGLWidget>
#include <QtGui\QOpenGLFunctions> 

class IGTopic;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

//	Q_OBJECT // must include this if you use Qt signals/slots

public:

	GLWidget(QWidget *parent = NULL);
	~GLWidget();

	void ActiveTexture(GLenum texture);

protected:

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:

	IGTopic* pInstance;

};
