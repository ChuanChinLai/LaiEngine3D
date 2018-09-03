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
		LaiEngine::Graphics::Effect::Create(pEffect, "Assets/Shaders/simple.vs", "Assets/Shaders/simple.fs");
	}


//	if (LaiEngine::Graphics::Mesh::Create(pMesh, "Assets/Models/nanosuit/nanosuit.obj"))
	if (LaiEngine::Graphics::Mesh::Create(pMesh, "Assets/Models/geometry/untitled.obj"))
	{
		pMesh->BindShader(pEffect);
	}


	{
		pLightGameObject = new LaiEngine::GameObject();
		pLightGameObject->Transform->Position = QVector3D(0.0f, 4.0f, 1.5f);
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

	LaiEngine::Camera::Create(pCamera);
	pCamera->SetSpeed(1.0f);

	pCamera->LookAt(QVector3D(0, 4.0f, 0), QVector3D(0, 0, 0), Camera::Up);
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
		pCamera->SetRotation(pCamera->GetRotation() + QVector3D(1, 0, 0));
		std::cout << pCamera->GetRotation() << std::endl;

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();

		return true;
	}

	if (event->key() == Qt::Key_S)
	{
		pCamera->SetRotation(pCamera->GetRotation() - QVector3D(1, 0, 0));
		std::cout << pCamera->GetRotation() << std::endl;

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}

	if (event->key() == Qt::Key_A)
	{
		pCamera->SetRotation(pCamera->GetRotation() + QVector3D(0, 1, 0));
		std::cout << pCamera->GetRotation() << std::endl;

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}

	if (event->key() == Qt::Key_D)
	{
		pCamera->SetRotation(pCamera->GetRotation() - QVector3D(0, 1, 0));
		std::cout << pCamera->GetRotation() << std::endl;

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}


	static QVector3D position = QVector3D(3, 0, 0);

	if (event->key() == Qt::Key_I)
	{
		position += QVector3D(0, 1, 0);
		std::cout << position << std::endl;

//		QMatrix4x4 viewMat;
//		viewMat.lookAt(position, QVector3D(0, 0, 0), QVector3D(0, 1, 0));
		pCamera->LookAt(position, QVector3D(0, 0, 0), QVector3D(0, 1, 0));

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}


	if (event->key() == Qt::Key_K)
	{
		position -= QVector3D(0, 1, 0);
		std::cout << position << std::endl;

		//		QMatrix4x4 viewMat;
		//		viewMat.lookAt(position, QVector3D(0, 0, 0), QVector3D(0, 1, 0));
		pCamera->LookAt(position, QVector3D(0, 0, 0), QVector3D(0, 1, 0));

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}

	if (event->key() == Qt::Key_J)
	{
		position -= QVector3D(1, 0, 0);
		std::cout << position << std::endl;

		//		QMatrix4x4 viewMat;
		//		viewMat.lookAt(position, QVector3D(0, 0, 0), QVector3D(0, 1, 0));
		pCamera->LookAt(position, QVector3D(0, 0, 0), QVector3D(0, 1, 0));

		pEffect->Bind();
		pEffect->SetUniformValue(pEffect->GetUniformLocation("cameraPosition_worldSpace"), pCamera->GetPosition());
		pEffect->UnBind();
		return true;
	}

	if (event->key() == Qt::Key_L)
	{
		position += QVector3D(1, 0, 0);
		std::cout << position << std::endl;

		//		QMatrix4x4 viewMat;
		//		viewMat.lookAt(position, QVector3D(0, 0, 0), QVector3D(0, 1, 0));
		pCamera->LookAt(position, QVector3D(0, 0, 0), QVector3D(0, 1, 0));

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

