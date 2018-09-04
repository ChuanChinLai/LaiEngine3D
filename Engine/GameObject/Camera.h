#pragma once

#include <QtGui\QMatrix4x4>

namespace LaiEngine
{
	class Camera 
	{
	public:

		static Camera* main;

		static bool Create(Camera*& o_camera, const QVector3D& position, const QVector3D& target);

		inline QVector3D GetPosition() const;
		inline QVector3D GetRotation() const;

		inline QMatrix4x4 GetViewMat() const;
		inline QMatrix4x4 GetProjectedMat() const;

		inline void SetPosition(const QVector3D& position);
		inline void SetRotation(const QVector3D& rotation);

		inline void SetSpeed(const float speed);

		void LookAt(const QVector3D& eye, const QVector3D& target, const QVector3D& up);

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();

		const static QVector3D Up;
		const static QVector3D Right;
		const static QVector3D Forward;
		const static QVector3D Backward;


	private:

		Camera(const QVector3D& position, const QVector3D& target);
	
		void UpdateViewMat();
		void UpdateRotationMat();

		float m_speed;

		QVector3D m_Position;
		QVector3D m_Rotation;

		QMatrix4x4 m_RotationMat;

		QMatrix4x4 m_ViewMat;
		QMatrix4x4 m_projectedMat;
	
	};
}

#include "Camera_inline.h"