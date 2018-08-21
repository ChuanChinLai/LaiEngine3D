#pragma once

#include <string>

namespace LaiEngine
{
	class GameObject;

	class IComponent
	{
	public:

		enum class Type
		{
			Transform, 
			MeshRenderer, 
			Light, 
			Null
		};


		virtual void Update() = 0;

		inline GameObject* GetGameObject() const
		{
			return m_pGameObject;
		};

		inline Type GetType() const
		{ 
			return m_Type;
		};

	protected:

		IComponent(GameObject* object) : m_pGameObject(object), m_Type(Type::Null)
		{

		}


		GameObject* m_pGameObject;
		Type m_Type;

	};
}