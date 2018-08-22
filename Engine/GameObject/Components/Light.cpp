#include "Light.h"

#include <Engine\Graphics\Effect.h>
#include <Engine\Graphics\Mesh.h>

#include <Engine\GameObject\GameObject.h>
#include <Engine\GameObject\Camera.h>
#include <Engine\GameObject\Components\Transform.h>


LaiEngine::Light::Light(GameObject * object) : IComponent(object), m_color(QVector3D(1, 1, 1)), m_pEffect(nullptr), m_pMesh(nullptr)
{
	m_Type = Type::Light;

	bool result = false;

	if (result = LaiEngine::Graphics::Effect::Create(m_pEffect, "Assets/Shaders/light.vs", "Assets/Shaders/light.fs"))
	{
		m_pEffect->SetUniformValue(m_pEffect->GetUniformLocation("lightColor"), m_color);
	}

	assert(result);

	if (result = LaiEngine::Graphics::Mesh::Create(m_pMesh, "Assets/Models/sphere/sphere.obj"))
	{
		m_pMesh->BindShader(m_pEffect);
	}

	assert(result);
}

LaiEngine::Light::~Light()
{
	LaiEngine::Graphics::Effect::Destroy(m_pEffect);
	LaiEngine::Graphics::Mesh::Destroy(m_pMesh);
}

void LaiEngine::Light::Update()
{
	if (m_pEffect == nullptr)
	{
		assert(false);
		return;
	}

	m_pEffect->Bind();


	QMatrix4x4 S;
	S.scale(m_pGameObject->Transform->Scale);
	QMatrix4x4 T;
	T.translate(m_pGameObject->Transform->Position);

	QMatrix4x4 modelMat = T * S;
	QMatrix4x4 viewMat = LaiEngine::Camera::main->GetViewMat();
	QMatrix4x4 projectedMat = LaiEngine::Camera::main->GetProjectedMat();


	m_pEffect->SetUniformValue(m_pEffect->GetUniformLocation("modelMat"), modelMat);
	m_pEffect->SetUniformValue(m_pEffect->GetUniformLocation("viewMat"), viewMat);
	m_pEffect->SetUniformValue(m_pEffect->GetUniformLocation("projectedMat"), projectedMat);

	m_pMesh->Render();

	m_pEffect->UnBind();
}

void LaiEngine::Light::SetColor(float R, float G, float B, float A)
{
	m_color.setX(R);
	m_color.setY(G);
	m_color.setZ(B);
	m_color.setW(A);

	if (m_pEffect != nullptr)
	{
		m_pEffect->SetUniformValue(m_pEffect->GetUniformLocation("lightColor"), m_color);
	}
	else
	{
		assert(false);
	}

}

QVector4D LaiEngine::Light::GetColor() const
{
	return m_color;
}
