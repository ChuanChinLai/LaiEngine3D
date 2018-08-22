#include "Header.h"

#include <Engine\Graphics\Effect.h>
#include <Engine\Graphics\Texture.h>

#include <Engine\Graphics\VertexFormats.h>
#include <Engine\Graphics\TextureFormats.h>

#include <Engine\Graphics\Mesh.h>
#include <Engine\GameEngine\GLWidget.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\GameObject\Camera.h>

#include <Engine\GameObject\Components\Transform.h>
#include <Engine\GameObject\Components\MeshRenderer.h>
#include <Engine\GameObject\Components\Light.h>

#include <QtGui\QMouseEvent>
#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>
#include <QtGui\QMatrix4x4>

#include <iostream>
#include <vector>
#include <memory>



LaiEngine::Graphics::Mesh* pMesh;
LaiEngine::Graphics::Effect* pEffect;

LaiEngine::GameObject* pGameObject;
LaiEngine::GameObject* pLightGameObject;

LaiEngine::Camera* pCamera;


LaiEngine::SimpleTriangle::SimpleTriangle(GLWidget* i_pGLWidget) : IScene(i_pGLWidget)
{

}

LaiEngine::SimpleTriangle::~SimpleTriangle()
{
	Destroy();
}

bool LaiEngine::SimpleTriangle::Init()
{
	{
		LaiEngine::Graphics::Effect::Create(pEffect, "Assets/Shaders/teapot.vs", "Assets/Shaders/teapot.fs");
	}


//	if (LaiEngine::Graphics::Mesh::Create(pMesh, "Assets/Models/nanosuit/nanosuit.obj"))
	if (LaiEngine::Graphics::Mesh::Create(pMesh, "Assets/Models/teapot.obj"))
	{
		pMesh->BindShader(pEffect);
	}


	{
		pLightGameObject = new LaiEngine::GameObject();
		pLightGameObject->Transform->Position = QVector3D(0, 4, 1.5f);
		pLightGameObject->AddComponent<LaiEngine::Light>();
	}


	pGameObject = new LaiEngine::GameObject();
	pGameObject->AddComponent<LaiEngine::MeshRenderer>();

	LaiEngine::MeshRenderer* pMeshRenderer = pGameObject->GetComponent<LaiEngine::MeshRenderer>();
	pMeshRenderer->SetMesh(pMesh);

	pGameObject->Transform->Scale = QVector3D(0.1f, 0.1f, 0.1f);

	LaiEngine::Camera::Create(pCamera);
	pCamera->SetSpeed(1.0f);
	pCamera->SetPosition(QVector3D(0, 200, 200));
	pCamera->SetRotation(QVector3D(-45.0f, 0, 0));

	return true;
}

void LaiEngine::SimpleTriangle::Update()
{
	std::cout << "Update" << std::endl;
	pLightGameObject->Update();
	pGameObject->Update();
}


bool LaiEngine::SimpleTriangle::Destroy()
{
	LaiEngine::Graphics::Effect::Destroy(pEffect);
	LaiEngine::Graphics::Mesh::Destroy(pMesh);

	delete pGameObject;
	delete pLightGameObject;

	delete pCamera;

	return true;
}

bool LaiEngine::SimpleTriangle::KeyPressEvent(QKeyEvent * event)
{
	std::cout << event->key() << std::endl;

	if (event->key() == Qt::Key_W)
	{
		pCamera->MoveForward();
		return true;
	}

	if (event->key() == Qt::Key_S)
	{
		pCamera->MoveBackward();
		return true;
	}

	if (event->key() == Qt::Key_A)
	{
		pCamera->MoveLeft();
		return true;
	}

	if (event->key() == Qt::Key_D)
	{
		pCamera->MoveRight();
		return true;
	}

	return false;
}

void LaiEngine::SimpleTriangle::MouseMoveEvent(QMouseEvent* event)
{
//	printf("%d, %d\n", event->x(), event->y());
}

