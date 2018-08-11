#include "IScene.h"

#include <Engine\Graphics\Effect.h>
#include <Engine\GameObject\GameObject.h>
#include <Engine\GameObject\Components\Transform.h>
#include <QtGui\QMatrix4x4>

static QMatrix4x4 modelMat;
static QMatrix4x4 viewMat;
static QMatrix4x4 projectedMat;

void IScene::PaintGL()
{
	for (size_t i = 0; i < m_DataRequiredToRenderAFrame.size(); i++)
	{
		LaiEngine::Graphics::Effect* pEffect = m_DataRequiredToRenderAFrame[i].pEffect;
		LaiEngine::GameObject* pGameObject = m_DataRequiredToRenderAFrame[i].pGameObject;

		pEffect->Bind();

		modelMat.scale(pGameObject->Transform->m_Scale);
//		viewMat.lookAt(QVector3D(0, 0, 500.0f), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
//		projectedMat.perspective(1.0f, 1.0f, 0.1f, 1000.0f);

		pEffect->SetUniformValue(pEffect->GetUniformLocation("modelMat"), modelMat);
//		pEffect->SetUniformValue(pEffect->GetUniformLocation("viewMat"), viewMat);
//		pEffect->SetUniformValue(pEffect->GetUniformLocation("projectedMat"), projectedMat);

		pGameObject->Update();
	}

	m_DataRequiredToRenderAFrame.clear();
}

void IScene::SubmitObjectToBeRendered(LaiEngine::Graphics::Effect * effect, LaiEngine::GameObject * object)
{
	sObjectRequiredToRenderAFrame data(effect, object);
	m_DataRequiredToRenderAFrame.push_back(data);
}
