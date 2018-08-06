#pragma once

class GLWidget;
class QKeyEvent;
class QMouseEvent;

class IGTopic
{
public:

	IGTopic(GLWidget* i_pGLWidget) : m_pGLWidget(i_pGLWidget) {};
	virtual ~IGTopic() {};

	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual bool Destroy() = 0;
	
	//virtual void KeyPressEvent(QKeyEvent* event) = 0;
	//virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event) = 0;

private:

	GLWidget* m_pGLWidget;
};