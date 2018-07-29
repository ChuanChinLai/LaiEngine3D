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


QMatrix4x4 m_Translation;
QMatrix4x4 m_Rotation;
QMatrix4x4 m_Scale;


// Create a colored triangle

Engine::Graphics::Mesh* pMesh;
Engine::Graphics::Mesh* pMesh1;

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
		m_effect = new Engine::Graphics::Effect("Assets/Shaders/simple.vs", "Assets/Shaders/simple.fs");
		m_effect->Bind();
	}


	std::vector<Engine::Graphics::VertexFormats::sMesh> data;

	{
		Engine::Graphics::VertexFormats::sMesh v1;
		v1.Position = QVector3D(0.5f, 0.5f, 0.0f);
		v1.Normal = QVector3D(0.0f, 1.0f, 0.0f);
		v1.UV = QVector2D(1.0f, 1.0f);
		data.push_back(v1);
	}

	{
		Engine::Graphics::VertexFormats::sMesh v2;
		v2.Position = QVector3D(0.5f, -0.5f, 0.0f);
		v2.Normal = QVector3D(1.0f, 0.0f, 0.0f);
		v2.UV = QVector2D(1.0f, -1.0f);
		data.push_back(v2);
	}

	{
		Engine::Graphics::VertexFormats::sMesh v3;
		v3.Position = QVector3D(-0.5f, -0.5f, 0.0f);
		v3.Normal = QVector3D(0.0f, 0.0f, 1.0f);
		v3.UV = QVector2D(-1.0f, -1.0f);
		data.push_back(v3);
	}

	{
		Engine::Graphics::VertexFormats::sMesh v4;
		v4.Position = QVector3D(-0.5f, 0.5f, 0.0f);
		v4.Normal = QVector3D(1.0f, 0.0f, 0.0f);
		v4.UV = QVector2D(-1.0f, 0.0f);
		data.push_back(v4);
	}

	const std::vector<unsigned int> sg_indices = { 0, 3, 1 };
	const std::vector<unsigned int> sg_indices1 = { 1, 3, 2 };
	const std::vector<Engine::Graphics::TextureFormats::sTexture> tex;
	
	pMesh = new Engine::Graphics::Mesh(data, sg_indices, tex);
	pMesh->Init(m_effect);

	pMesh1 = new Engine::Graphics::Mesh(data, sg_indices1, tex);
	pMesh1->Init(m_effect);


	return true;
}

void SimpleTriangle::Update()
{
	pMesh->Render();
	pMesh1->Render();
}

bool SimpleTriangle::Destroy()
{

	delete m_effect;
	delete pMesh;
	delete pMesh1;

	return true;
}

void SimpleTriangle::MouseMoveEvent(QMouseEvent* event)
{
	printf("%d, %d\n", event->x(), event->y());
}

