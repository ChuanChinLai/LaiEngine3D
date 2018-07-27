#pragma once

class GLWidget;

class IGTopic
{
public:

	IGTopic(GLWidget* i_pGLWidget) : m_pGLWidget(i_pGLWidget) {};
	virtual ~IGTopic() {};

	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual bool Destroy() = 0;
	
	GLWidget* GetWidget() const { return m_pGLWidget; };

private:

	GLWidget* m_pGLWidget;
};