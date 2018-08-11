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
			m_GUID = "{04C0DAC2-4289-4920-8279-7CEFCF7A6A1B}";
		};


		void Update() override;

		void SetMesh(Graphics::Mesh* mesh);

	private:

		Graphics::Mesh* m_pMesh;

	};
}