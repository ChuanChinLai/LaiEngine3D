#include "Light.h"

void LaiEngine::Light::Update()
{

}

void LaiEngine::Light::SetColor(float R, float G, float B, float A)
{
	m_color.setX(R);
	m_color.setY(G);
	m_color.setZ(B);
	m_color.setW(A);
}

QVector4D LaiEngine::Light::GetColor() const
{
	return m_color;
}
