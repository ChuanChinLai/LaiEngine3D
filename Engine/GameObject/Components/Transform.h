#pragma once

#include "IComponent.h"

#include <QtGui\Qvector3D>

namespace LaiEngine
{
	class Transform : public IComponent
	{
	public:

		Transform(GameObject* object) : IComponent(object), m_Position(), m_Rotation(), m_Scale(0, 0, 0)
		{
			m_GUID = "{170A9005-E3D4-4367-B4D6-5012CBD8A0FC}";
		};

		void Update() override
		{

		}


		QVector3D m_Position;
		QVector3D m_Rotation;
		QVector3D m_Scale;
	};
}