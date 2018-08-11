#include "Header.h"

#include <Engine\Graphics\Effect.h>
#include <Engine\Graphics\Texture.h>

#include <Engine\Graphics\VertexFormats.h>
#include <Engine\Graphics\TextureFormats.h>

#include <Engine\Graphics\Mesh.h>
#include <Engine\GameEngine\GLWidget.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\GameObject\Components\MeshRenderer.h>
#include <Engine\GameObject\Components\Transform.h>

#include <QtGui\QMouseEvent>
#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>
#include <QtGui\QMatrix4x4>

#include <iostream>
#include <vector>
#include <memory>


QVector3D cameraPosition(0, 0, 0);
QVector3D objScale(0.01f, 0.01f, 0.01f);

QMatrix4x4 modelMat;
QMatrix4x4 viewMat;
QMatrix4x4 projectedMat;


LaiEngine::Graphics::Mesh* pMesh;
LaiEngine::Graphics::Effect* pEffect;

LaiEngine::GameObject* pGameObject;

SimpleTriangle::SimpleTriangle(GLWidget* i_pGLWidget) : IScene(i_pGLWidget)
{

}

SimpleTriangle::~SimpleTriangle()
{
	Destroy();
}

bool SimpleTriangle::Init()
{
	{
		LaiEngine::Graphics::Effect::Create(pEffect, "Assets/Shaders/simple.vs", "Assets/Shaders/simple.fs");
	}


//	if (LaiEngine::Graphics::Mesh::Create(pMesh, "Assets/Models/nanosuit/nanosuit.obj"))
	if (LaiEngine::Graphics::Mesh::Create(pMesh, "Assets/Models/teapot.obj"))
	{
		pMesh->BindShader(pEffect);
	}

	pGameObject = new LaiEngine::GameObject();
	pGameObject->AddComponent<LaiEngine::MeshRenderer>();

	LaiEngine::MeshRenderer* pMeshRenderer = pGameObject->GetComponent<LaiEngine::MeshRenderer>();
	pMeshRenderer->SetMesh(pMesh);

	pGameObject->Transform->m_Scale = QVector3D(0.01f, 0.01f, 0.01f);


	return true;
}

void SimpleTriangle::Update()
{
	std::cout << "Update" << std::endl;
	SubmitObjectToBeRendered(pEffect, pGameObject);

	pEffect->Bind();

	modelMat.scale(QVector3D(0.1f, 0.1f, 0.1f));
//	viewMat.lookAt(QVector3D(0, 0, 500.0f), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
//	projectedMat.perspective(1.0f, 1.0f, 0.1f, 1000.0f);


	pEffect->SetUniformValue(pEffect->GetUniformLocation("modelMat"), modelMat);


//	pEffect->SetUniformValue(pEffect->GetUniformLocation("viewMat"), viewMat);
//	pEffect->SetUniformValue(pEffect->GetUniformLocation("projectedMat"), projectedMat);

	pMesh->Render();
}


bool SimpleTriangle::Destroy()
{
	LaiEngine::Graphics::Effect::Destroy(pEffect);
	LaiEngine::Graphics::Mesh::Destroy(pMesh);

	delete pGameObject;

	return true;
}

void SimpleTriangle::KeyPressEvent(QKeyEvent * event)
{
	std::cout << event->key() << std::endl;

	if (event->key() == Qt::Key_W)
	{
		cameraPosition = QVector3D(0, 0.01f, 0);
	}

	if (event->key() == Qt::Key_S)
	{
		cameraPosition = QVector3D(0, -0.01f, 0);
	}
}

void SimpleTriangle::MouseMoveEvent(QMouseEvent* event)
{
//	printf("%d, %d\n", event->x(), event->y());
}

