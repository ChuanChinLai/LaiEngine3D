#pragma once

#include <Engine\Graphics\IGraphicsProject\IGraphicsProject.h>

class QOpenGLVertexArrayObject;
class QOpenGLShaderProgram;
class QOpenGLBuffer;


class SimpleTriangle : public IGraphicsProject
{
public:

	SimpleTriangle();
	~SimpleTriangle();

	bool Init() override;
	void Update() override;
	bool Destroy() override;

private:

	// OpenGL State Information
	QOpenGLVertexArrayObject * m_object;
	QOpenGLShaderProgram *m_program;

	QOpenGLBuffer* m_vertex;
	QOpenGLBuffer* m_index;
};