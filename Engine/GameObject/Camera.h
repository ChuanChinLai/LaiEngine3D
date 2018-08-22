#pragma once

#include <QtGui\QMatrix4x4>

namespace LaiEngine
{
	class Camera 
	{
	public:

		static Camera* main;

		static bool Create(Camera*& o_camera);

		inline QMatrix4x4 GetViewMat() const;
		inline QMatrix4x4 GetProjectedMat() const;

		inline void SetPosition(const QVector3D& position);
		inline void SetRotation(const QVector3D& rotation);

		inline void SetSpeed(const float speed);
		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();




	private:

		Camera();
	
		void UpdateViewMat();
		void UpdateRotationMat();

		float m_speed;

		QVector3D m_Position;
		QVector3D m_Rotation;

		QMatrix4x4 m_RotationMat;

		QMatrix4x4 m_ViewMat;
		QMatrix4x4 m_projectedMat;
		
		const static QVector3D Up;
		const static QVector3D Right;
		const static QVector3D Forward;
		const static QVector3D Backward;
	};
}

#include "Camera_inline.h"