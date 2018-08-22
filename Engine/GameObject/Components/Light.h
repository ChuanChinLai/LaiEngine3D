#pragma once

#include "IComponent.h"

#include <QtGui\Qvector4D>

namespace LaiEngine
{
	namespace Graphics
	{
		class Mesh;
		class Effect;
	}

	class Light : public IComponent
	{
	public:

		Light(GameObject* object);
		~Light();


		void Update() override;

		void SetColor(float R, float G, float B, float A);
		QVector4D GetColor() const;

	private:

		QVector4D m_color;

		Graphics::Effect* m_pEffect;
		Graphics::Mesh*   m_pMesh;
	};
}