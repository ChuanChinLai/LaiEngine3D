#pragma once

#include <QtWidgets\QOpenGLWidget>
#include <QtGui\QOpenGLFunctions> 

class IGTopic;

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions
{

//	Q_OBJECT // must include this if you use Qt signals/slots

public:

	GLWidget(QWidget* parent = nullptr);
	~GLWidget();

protected:

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:

	IGTopic* m_pInstance;
};
