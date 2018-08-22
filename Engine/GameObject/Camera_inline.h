#pragma once

#include "Camera.h"

inline QMatrix4x4 LaiEngine::Camera::GetViewMat() const
{
	return m_ViewMat;
}

inline QMatrix4x4 LaiEngine::Camera::GetProjectedMat() const
{
	return m_projectedMat;
}

inline void LaiEngine::Camera::SetPosition(const QVector3D & position)
{
	m_Position = position;
	UpdateViewMat();
}

inline void LaiEngine::Camera::SetRotation(const QVector3D & rotation)
{
	m_Rotation = rotation;
	UpdateRotationMat();
	UpdateViewMat();
}

void LaiEngine::Camera::SetSpeed(const float speed)
{
	m_speed = speed;
}

inline void LaiEngine::Camera::MoveForward()
{
	QVector3D cameraForward = m_RotationMat * Forward;
	QVector3D delta = cameraForward.normalized() * m_speed;

	QMatrix4x4 Translation;
	Translation.translate(delta);

	m_Position = Translation * m_Position;
	UpdateViewMat();
}

inline void LaiEngine::Camera::MoveBackward()
{
	QVector3D cameraBackward = m_RotationMat * Backward;
	QVector3D delta = cameraBackward.normalized() * m_speed;

	QMatrix4x4 Translation;
	Translation.translate(delta);

	m_Position = Translation * m_Position;
	UpdateViewMat();
}

inline void LaiEngine::Camera::MoveLeft()
{
	QVector3D cameraUp = m_RotationMat * Up;
	QVector3D cameraForward = m_RotationMat * Forward;

	QVector3D cameraLeft = QVector3D::crossProduct(cameraUp, cameraForward);
	QVector3D delta = cameraLeft.normalized() * m_speed;

	QMatrix4x4 Translation;
	Translation.translate(delta);

	m_Position = Translation * m_Position;
	UpdateViewMat();
}

inline void LaiEngine::Camera::MoveRight()
{
	QVector3D cameraUp = m_RotationMat * Up;
	QVector3D cameraForward = m_RotationMat * Forward;

	QVector3D cameraRight = -QVector3D::crossProduct(cameraUp, cameraForward);
	QVector3D delta = cameraRight.normalized() * m_speed;

	QMatrix4x4 Translation;
	Translation.translate(delta);

	m_Position = Translation * m_Position;
	UpdateViewMat();
}
