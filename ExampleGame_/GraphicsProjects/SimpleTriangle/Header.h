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

namespace LaiEngine
{
	class SimpleTriangle : public IScene
	{
	public:

		SimpleTriangle(GLWidget* i_pGLWidget);
		~SimpleTriangle();

		bool Init() override;
		void Update() override;
		bool Destroy() override;

		bool KeyPressEvent(QKeyEvent* event) override;
		void MouseMoveEvent(QMouseEvent* event) override;

	private:

	};
}