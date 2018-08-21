#include "GameObject.h"


#include "Components\Transform.h"

LaiEngine::GameObject::GameObject() : Transform(new LaiEngine::Transform(this))
{
	m_Components[IComponent::Type::Transform] = Transform;
}

LaiEngine::GameObject::~GameObject()
{
	for (auto component : m_Components)
	{
		if (component.second != nullptr)
		{
			delete component.second;
		}
	}
}

void LaiEngine::GameObject::Update()
{
	for (const auto& i : m_Components)
	{
		i.second->Update();
	}
}
