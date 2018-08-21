#include "MeshRenderer.h"

#include <Engine\Graphics\Mesh.h>
#include <Engine\Graphics\Effect.h>
#include <Engine\GameObject\Camera.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\GameObject\Components\Transform.h>

#include <QtGui\QMatrix4x4>

void LaiEngine::MeshRenderer::Update()
{
	LaiEngine::Graphics::Effect* pEffect = m_pMesh->GetShader();
	
	if (pEffect == nullptr)
	{
		assert(false);
		return;
	}

	pEffect->Bind();


	QMatrix4x4 modelMat;
	QMatrix4x4 viewMat;
	QMatrix4x4 projectedMat;

	LaiEngine::GameObject* pGameObject = m_pGameObject;

	modelMat.scale(pGameObject->Transform->Scale);

	viewMat = LaiEngine::Camera::main->GetViewMat();

	projectedMat.perspective(1.0f, 1.0f, 0.001f, 100000.0f);

	pEffect->SetUniformValue(pEffect->GetUniformLocation("modelMat"), modelMat);
	pEffect->SetUniformValue(pEffect->GetUniformLocation("viewMat"), viewMat);
	pEffect->SetUniformValue(pEffect->GetUniformLocation("projectedMat"), projectedMat);

	m_pMesh->Render();

	pEffect->UnBind();
}

void LaiEngine::MeshRenderer::SetMesh(Graphics::Mesh * mesh)
{
	m_pMesh = mesh;
}
