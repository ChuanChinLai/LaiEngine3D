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


	QMatrix4x4 S;
	S.scale(m_pGameObject->Transform->Scale);
	QMatrix4x4 T;
	T.translate(m_pGameObject->Transform->Position);

	QMatrix4x4 modelMat = T * S;
	QMatrix4x4 viewMat = LaiEngine::Camera::main->GetViewMat();
	QMatrix4x4 projectedMat = LaiEngine::Camera::main->GetProjectedMat();

	pEffect->SetUniformValue(pEffect->GetUniformLocation("modelMat"), modelMat);
	pEffect->SetUniformValue(pEffect->GetUniformLocation("viewMat"), viewMat);
	pEffect->SetUniformValue(pEffect->GetUniformLocation("projectedMat"), projectedMat);

	m_pMesh->Render();

	pEffect->UnBind();
}

void LaiEngine::MeshRenderer::SetMesh(Graphics::Mesh* mesh)
{
	m_pMesh = mesh;
}
