#pragma once

#include <vector>

class GLWidget;
class QKeyEvent;
class QMouseEvent;

namespace LaiEngine
{
	namespace Graphics
	{
		class Effect;
	}
}

namespace LaiEngine
{
	class GameObject;
	class Camera; 

	class IScene
	{
	public:

		IScene(GLWidget* i_pGLWidget) : m_pGLWidget(i_pGLWidget) {};
		virtual ~IScene() {};

		virtual bool Init() = 0;
		virtual void Update() = 0;
		virtual bool Destroy() = 0;

		virtual bool KeyPressEvent(QKeyEvent* event) = 0;
		//virtual void MousePressEvent(QMouseEvent *event) = 0;
		virtual void MouseMoveEvent(QMouseEvent *event) = 0;

	private:

		GLWidget* m_pGLWidget;
	};
}