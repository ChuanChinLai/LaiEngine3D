#pragma once

#include "IComponent.h"

namespace LaiEngine
{
	namespace Graphics
	{
		class Mesh;
	}

	class MeshRenderer : public IComponent
	{
	public:

		MeshRenderer(GameObject* object) : IComponent(object), m_pMesh(nullptr)
		{
			m_Type = Type::MeshRenderer;
		};


		void Update() override;

		void SetMesh(Graphics::Mesh* mesh);

	private:

		Graphics::Mesh* m_pMesh;

	};
}