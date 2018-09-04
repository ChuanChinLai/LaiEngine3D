#include "Camera.h"

const QVector3D LaiEngine::Camera::Up       = QVector3D( 0.0f,  1.0f,  0.01f );
const QVector3D LaiEngine::Camera::Right    = QVector3D( 1.0f,  0.0f,  0.0f );
const QVector3D LaiEngine::Camera::Forward  = QVector3D( 0.0f,  0.0f, -1.0f );
const QVector3D LaiEngine::Camera::Backward = QVector3D( 0.0f,  0.0f,  1.0f );

LaiEngine::Camera* LaiEngine::Camera::main = nullptr;

bool LaiEngine::Camera::Create(Camera *& o_camera, const QVector3D& position, const QVector3D& target)
{
	if (o_camera != nullptr)
		delete o_camera;


	o_camera = new Camera(position, target);
	o_camera->m_projectedMat.perspective(45.0f, 1.0f, 0.0f, 1000.0f);


	if (main == nullptr)
		main = o_camera;

	return true;
}

void LaiEngine::Camera::LookAt(const QVector3D& eye, const QVector3D& target, const QVector3D& up)
{
	m_Position = eye;

	QVector3D forward = (target - eye).normalized();
	QVector3D side = QVector3D::crossProduct(forward, up).normalized();
	QVector3D upVector = QVector3D::crossProduct(side, forward).normalized();

	//QMatrix4x4 m(side.x(), upVector.x(), -forward.x(), 0.0f, 
	//	         side.y(), upVector.y(), -forward.y(), 0.0f, 
	//	         side.z(), upVector.z(), -forward.z(), 0.0f, 
	//	             0.0f,         0.0f,         0.0f, 1.0f);


	QMatrix4x4 m(    side.x(),     side.y(),     side.z(), 0.0f,
		         upVector.x(), upVector.y(), upVector.z(), 0.0f,
		         -forward.x(), -forward.y(), -forward.z(), 0.0f,
		                 0.0f,         0.0f,         0.0f, 1.0f);



	m_ViewMat.setToIdentity();
	m_ViewMat *= m;
	m_ViewMat.translate(-eye);
}


void LaiEngine::Camera::UpdateViewMat()
{
	QVector3D cameraForward = m_RotationMat * Forward;
	QVector3D cameraTarget = m_Position + cameraForward;

	LookAt(m_Position, cameraTarget, Up);
}

void LaiEngine::Camera::UpdateRotationMat()
{
	m_RotationMat.setToIdentity();
	m_RotationMat.rotate(m_Rotation.x(), QVector3D(1.0f, 0, 0));
	m_RotationMat.rotate(m_Rotation.y(), QVector3D(0, 1.0f, 0));
}


LaiEngine::Camera::Camera(const QVector3D& position, const QVector3D& target) : m_speed(1.0f)
{
	LookAt(position, target, Up);
}