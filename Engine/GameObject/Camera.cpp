#include "Camera.h"

const QVector3D LaiEngine::Camera::Up       = QVector3D( 0.0f,  1.0f,  0.0f );
const QVector3D LaiEngine::Camera::Right    = QVector3D( 1.0f,  0.0f,  0.0f );
const QVector3D LaiEngine::Camera::Forward  = QVector3D( 0.0f,  0.0f, -1.0f );
const QVector3D LaiEngine::Camera::Backward = QVector3D( 0.0f,  0.0f,  1.0f );

LaiEngine::Camera* LaiEngine::Camera::main = nullptr;

bool LaiEngine::Camera::Create(Camera *& o_camera)
{
	if (o_camera != nullptr)
		delete o_camera;


	o_camera = new Camera;
	o_camera->m_projectedMat.perspective(1.0f, 1.0f, 0.001f, 100000.0f);


	if (main == nullptr)
		main = o_camera;

	return true;
}


LaiEngine::Camera::Camera() : m_speed(1.0f)
{
	UpdateRotationMat();
	UpdateViewMat();
}

void LaiEngine::Camera::UpdateViewMat()
{
	QVector3D cameraForward = m_RotationMat * Forward;
	QVector3D cameraTarget = m_Position + cameraForward;

	m_ViewMat.setToIdentity();
	m_ViewMat.lookAt(m_Position, cameraTarget, Up);
}

void LaiEngine::Camera::UpdateRotationMat()
{
	m_RotationMat.setToIdentity();
	m_RotationMat.rotate(m_Rotation.x(), QVector3D(1.0f, 0, 0));
	m_RotationMat.rotate(m_Rotation.y(), QVector3D(0, 1.0f, 0));
}
