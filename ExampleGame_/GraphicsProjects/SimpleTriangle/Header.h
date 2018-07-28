#pragma once

#include <Engine\Graphics\IGTopic.h>

class QOpenGLVertexArrayObject;;
class QOpenGLBuffer;

namespace Engine
{
	namespace Graphics
	{
		class Effect;
	}
}


class SimpleTriangle : public IGTopic
{
public:

	SimpleTriangle(GLWidget* i_pGLWidget);
	~SimpleTriangle();

	bool Init() override;
	void Update() override;
	bool Destroy() override;

	void MouseMoveEvent(QMouseEvent *event) override;

private:

	// OpenGL State Information
	QOpenGLVertexArrayObject* m_object;
	Engine::Graphics::Effect* m_effect;

	QOpenGLBuffer* m_vertex;
	QOpenGLBuffer* m_index;
};