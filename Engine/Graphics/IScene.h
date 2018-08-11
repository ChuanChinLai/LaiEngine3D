#pragma once

#include <vector>

class GLWidget;
class QKeyEvent;
class QMouseEvent;

namespace LaiEngine
{
	class GameObject;

	namespace Graphics
	{
		class Effect;
	}
}


class IScene
{
public:

	struct sObjectRequiredToRenderAFrame
	{
		sObjectRequiredToRenderAFrame(LaiEngine::Graphics::Effect* effect, LaiEngine::GameObject* object)
		{
			pEffect = effect;
			pGameObject = object;
		}

		LaiEngine::Graphics::Effect* pEffect;
		LaiEngine::GameObject* pGameObject;
	};

	IScene(GLWidget* i_pGLWidget) : m_pGLWidget(i_pGLWidget) {};
	virtual ~IScene() {};

	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual bool Destroy() = 0;
	
	virtual void KeyPressEvent(QKeyEvent* event) = 0;
	//virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event) = 0;


	void PaintGL();
	void SubmitObjectToBeRendered(LaiEngine::Graphics::Effect* effect, LaiEngine::GameObject* object);


private:

	std::vector<sObjectRequiredToRenderAFrame> m_DataRequiredToRenderAFrame;

	GLWidget * m_pGLWidget;
};