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

	Engine::Graphics::Effect* m_effect;
};