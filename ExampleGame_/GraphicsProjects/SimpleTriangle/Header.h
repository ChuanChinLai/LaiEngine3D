#pragma once

#include <Engine\Graphics\IScene.h>

class QOpenGLVertexArrayObject;;
class QOpenGLBuffer;

namespace LaiEngine
{
	namespace Graphics
	{
		class Effect;
	}
}


class SimpleTriangle : public IScene
{
public:

	SimpleTriangle(GLWidget* i_pGLWidget);
	~SimpleTriangle();

	bool Init() override;
	void Update() override;
	bool Destroy() override;

	void KeyPressEvent(QKeyEvent* event) override;
	void MouseMoveEvent(QMouseEvent* event) override;

private:

};