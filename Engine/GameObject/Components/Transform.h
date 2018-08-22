#pragma once

#include "IComponent.h"

#include <QtGui\Qvector3D>

namespace LaiEngine
{
	class Transform : public IComponent
	{
	public:

		Transform(GameObject* object) : IComponent(object), Position(0, 0, 0), Rotation(0, 0, 0), Scale(1, 1, 1)
		{
			m_Type = Type::Transform;
		};

		void Update() override
		{

		}


		QVector3D Position;
		QVector3D Rotation;
		QVector3D Scale;
	};
}