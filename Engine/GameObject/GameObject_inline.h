#pragma once

#include "GameObject.h"
#include "Components\IComponent.h"

template<typename T>
inline void LaiEngine::GameObject::AddComponent()
{
	IComponent* pComponent = new T(this);

	const IComponent::Type& type = pComponent->GetType();

	if (m_Components[type] == nullptr)
	{
		m_Components[type] = pComponent;
	}
	else
	{
		delete pComponent;
	}
}

template<typename T>
inline T* LaiEngine::GameObject::GetComponent()
{
	IComponent* pDummy = new T(this);

	const IComponent::Type& type = pDummy->GetType();

	T* pComponent = dynamic_cast<T*>(m_Components[type]);

	delete pDummy;

	return pComponent;
}