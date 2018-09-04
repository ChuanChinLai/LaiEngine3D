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

static QVector3D cameraPosition = QVector3D(0.001f,10.0f, 0);
static QVector3D lightPosition  = QVector3D(0.0f, 15.0f, 0.0f);

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
	if (LaiEngine::Graphics::Mesh::Create(pMesh, "Assets/Models/geometry/cube.obj"))
	{
		pMesh->BindShader(pEffect);
	}


	{
		pLightGameObject = new LaiEngine::GameObject();
		pLightGameObject->Transform->Position = lightPosition;
		pLightGameObject->AddComponent<LaiEngine::Light>();

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("lightPosition_worldSpace"), pLightGameObject->Transform->Position);
		pEffect->UnBind();
	}


	pGameObject = new LaiEngine::GameObject();
	pGameObject->AddComponent<LaiEngine::MeshRenderer>();

	LaiEngine::MeshRenderer* pMeshRenderer = pGameObject->GetComponent<LaiEngine::MeshRenderer>();
	pMeshRenderer->SetMesh(pMesh);
//	pGameObject->Transform->Rotation = QVector3D(-90, 0, 0);
//	pGameObject->Transform->Scale = QVector3D(0.1f, 0.1f, 0.1f);

	LaiEngine::Camera::Create(pCamera, cameraPosition, QVector3D(0, 0, 0));
	pCamera->SetSpeed(1.0f);

//	pCamera->SetPosition(QVector3D(0, 200, 0));
//	pCamera->SetRotation(QVector3D(-90, 0, 0));

	pEffect->Bind();
	pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
	pEffect->UnBind();
	
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

std::ostream& operator<<(std::ostream& os, const QVector3D& v)
{
	std::cout << "(" << v.x() << "." << v.y() << "." << v.z() << ")" << std::endl;
	return os;
}

bool LaiEngine::SimpleTriangle::KeyPressEvent(QKeyEvent * event)
{
	std::cout << event->key() << std::endl;

	if (event->key() == Qt::Key_W)
	{
		lightPosition -= QVector3D(0, 0, 1);
		std::cout << lightPosition << std::endl;
		pLightGameObject->Transform->Position = lightPosition;

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("lightPosition_worldSpace"), pLightGameObject->Transform->Position);
		pEffect->UnBind();

		return true;
	}

	if (event->key() == Qt::Key_S)
	{
		lightPosition += QVector3D(0, 0, 1);
		std::cout << lightPosition << std::endl;
		pLightGameObject->Transform->Position = lightPosition;

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("lightPosition_worldSpace"), pLightGameObject->Transform->Position);
		pEffect->UnBind();

		return true;
	}

	if (event->key() == Qt::Key_A)
	{
		lightPosition -= QVector3D(1, 0, 0);
		std::cout << lightPosition << std::endl;
		pLightGameObject->Transform->Position = lightPosition;

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("lightPosition_worldSpace"), pLightGameObject->Transform->Position);
		pEffect->UnBind();

		return true;
	}

	if (event->key() == Qt::Key_D)
	{
		lightPosition += QVector3D(1, 0, 0);
		std::cout << lightPosition << std::endl;
		pLightGameObject->Transform->Position = lightPosition;

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("lightPosition_worldSpace"), pLightGameObject->Transform->Position);
		pEffect->UnBind();

		return true;
	}


	//Camera // 

	if (event->key() == Qt::Key_I)
	{
		cameraPosition += QVector3D(0, 1, 0);
		std::cout << cameraPosition << std::endl;
		pCamera->LookAt(cameraPosition, QVector3D(0, 0, 0), QVector3D(0, 1, 0));

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}


	if (event->key() == Qt::Key_K)
	{
		cameraPosition -= QVector3D(0, 1, 0);
		std::cout << cameraPosition << std::endl;
		pCamera->LookAt(cameraPosition, QVector3D(0, 0, 0), QVector3D(0, 1, 0));

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}

	if (event->key() == Qt::Key_J)
	{
		cameraPosition -= QVector3D(1, 0, 0);
		std::cout << cameraPosition << std::endl;
		pCamera->LookAt(cameraPosition, QVector3D(0, 0, 0), QVector3D(0, 1, 0));

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}

	if (event->key() == Qt::Key_L)
	{
		cameraPosition += QVector3D(1, 0, 0);
		std::cout << cameraPosition << std::endl;
		pCamera->LookAt(cameraPosition, QVector3D(0, 0, 0), QVector3D(0, 1, 0));

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}


	return false;
}

void LaiEngine::SimpleTriangle::MouseMoveEvent(QMouseEvent* event)
{
//	printf("%d, %d\n", event->x(), event->y());
}

