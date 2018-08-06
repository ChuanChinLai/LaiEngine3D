#include "Header.h"

#include <Engine\Graphics\Effect.h>
#include <Engine\Graphics\Texture.h>

#include <Engine\Graphics\VertexFormats.h>
#include <Engine\Graphics\TextureFormats.h>

#include <Engine\Graphics\Mesh.h>

#include <Engine\GameEngine\GLWidget.h>


#include <QtGui\QMouseEvent>
#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>
#include <QtGui\QMatrix4x4>

#include <iostream>
#include <vector>
#include <memory>

QMatrix4x4 m_Translation;
QMatrix4x4 m_Rotation;
QMatrix4x4 m_Scale;


// Create a colored triangle

Engine::Graphics::Mesh* pMesh;
Engine::Graphics::Effect* pEffect;

SimpleTriangle::SimpleTriangle(GLWidget* i_pGLWidget) : IGTopic(i_pGLWidget)
{

}

SimpleTriangle::~SimpleTriangle()
{
	Destroy();
}

bool SimpleTriangle::Init()
{
	{
		// Create Shader (Do not release until VAO is created)
		Engine::Graphics::Effect::Create(pEffect, "Assets/Shaders/simple.vs", "Assets/Shaders/simple.fs");
		pEffect->Bind();
	}

	if (Engine::Graphics::Mesh::Create(pMesh, "Assets/Models/nanosuit/nanosuit.obj"))
	{
		pMesh->BindShader(pEffect);
	}


	return true;
}

void SimpleTriangle::Update()
{
	pMesh->Render();
}

bool SimpleTriangle::Destroy()
{
	Engine::Graphics::Effect::Destroy(pEffect);
	Engine::Graphics::Mesh::Destroy(pMesh);

	return true;
}

void SimpleTriangle::MouseMoveEvent(QMouseEvent* event)
{
	printf("%d, %d\n", event->x(), event->y());
}

