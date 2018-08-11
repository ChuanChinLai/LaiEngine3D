#pragma once

#include <string>

namespace LaiEngine
{
	class GameObject;

	class IComponent
	{
	public:

		virtual void Update() = 0;

		inline GameObject* GetGameObject() const
		{
			return m_pGameObject;
		};

		inline std::string GetGUID() const
		{ 
			return m_GUID;
		};

	protected:

		IComponent(GameObject* object) : m_pGameObject(object), m_GUID("")
		{

		}


		GameObject* m_pGameObject;
		std::string m_GUID;

	};
}