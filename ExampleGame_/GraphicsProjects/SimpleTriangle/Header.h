#pragma once

#include <Engine\Graphics\IGraphicsProject\IGraphicsProject.h>

class QOpenGLVertexArrayObject;;
class QOpenGLBuffer;

namespace Engine
{
	namespace Graphics
	{
		class Effect;
	}
}


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
	QOpenGLVertexArrayObject* m_object;
	Engine::Graphics::Effect* m_effect;

	QOpenGLBuffer* m_vertex;
	QOpenGLBuffer* m_index;
};