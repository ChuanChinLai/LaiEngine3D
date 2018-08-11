#pragma once

#include "GameObject.h"
#include "Components\IComponent.h"

template<typename T>
inline void LaiEngine::GameObject::AddComponent()
{
	IComponent* pComponent = new T(this);

	const std::string& Guid = pComponent->GetGUID();

	if (m_Components[Guid] == nullptr)
	{
		m_Components[Guid] = pComponent;
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

	const std::string& Guid = pDummy->GetGUID();

	T* pComponent = dynamic_cast<T*>(m_Components[Guid]);

	delete pDummy;

	return pComponent;
}