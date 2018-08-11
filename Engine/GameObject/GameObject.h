#pragma once

#include "Components\IComponent.h"

#include <string>
#include <unordered_map>

namespace LaiEngine
{
	class Transform;

	class GameObject
	{
	public:

		GameObject();
		~GameObject();

		Transform* Transform;

		void Update();

		template<typename T>
		inline void AddComponent();

		template<typename T>
		inline T*	GetComponent();



	private:


		GameObject(const GameObject& i_Object);
		GameObject& operator =  (const GameObject& i_Object);

		std::unordered_map<std::string, IComponent*> m_Components;
	};
}

#include "GameObject_inline.h"