#include "Header.h"

#include <Engine\Graphics\Effect.h>
#include <Engine\Graphics\Texture.h>

#include <Engine\Graphics\VertexFormats.h>
#include <Engine\Graphics\TextureFormats.h>

#include <Engine\Graphics\Mesh.h>

#include <Engine\GameEngine\GLWidget.h>


#if defined(_DEBUG)
#	define ENG_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define ENG_NEW new
#endif

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

	int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	// tmpDbgFlag |= _CRTDBG_ALLOC_MEM_DF;
	_CrtSetDbgFlag(tmpDbgFlag);
	auto prt = ENG_NEW int(10);
	auto c = new char('a');


	//{
	//	Engine::Graphics::VertexFormats::sMesh v1;
	//	v1.Position = QVector3D(0.5f, 0.5f, 0.0f);
	//	v1.Normal = QVector3D(0.0f, 1.0f, 0.0f);
	//	v1.UV = QVector2D(1.0f, 1.0f);
	//	data.push_back(v1);
	//}

	//{
	//	Engine::Graphics::VertexFormats::sMesh v2;
	//	v2.Position = QVector3D(0.5f, -0.5f, 0.0f);
	//	v2.Normal = QVector3D(1.0f, 0.0f, 0.0f);
	//	v2.UV = QVector2D(1.0f, -1.0f);
	//	data.push_back(v2);
	//}

	//{
	//	Engine::Graphics::VertexFormats::sMesh v3;
	//	v3.Position = QVector3D(-0.5f, -0.5f, 0.0f);
	//	v3.Normal = QVector3D(0.0f, 0.0f, 1.0f);
	//	v3.UV = QVector2D(-1.0f, -1.0f);
	//	data.push_back(v3);
	//}

	//{
	//	Engine::Graphics::VertexFormats::sMesh v4;
	//	v4.Position = QVector3D(-0.5f, 0.5f, 0.0f);
	//	v4.Normal = QVector3D(1.0f, 0.0f, 0.0f);
	//	v4.UV = QVector2D(-1.0f, 0.0f);
	//	data.push_back(v4);
	//}


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

