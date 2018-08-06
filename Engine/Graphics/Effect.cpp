#include "Effect.h"

#include <QtGui\QOpenGLFunctions> 
#include <QtGui\QOpenGLShaderProgram>

#include <iostream>
#include <cassert>

bool Engine::Graphics::Effect::Create(Effect *& o_effect, const QString& vShaderName, const QString& fShaderName)
{
	if (o_effect != nullptr)
		delete o_effect;

	o_effect = new Effect(vShaderName, fShaderName);

	return true;
}

bool Engine::Graphics::Effect::Destroy(Effect *& o_effect)
{
	if (o_effect != nullptr)
		delete o_effect;

	return true;
}

void Engine::Graphics::Effect::Bind() const
{
	if (m_pShaderProgram != nullptr)
	{
		bool success = m_pShaderProgram->bind();
		if (!success) assert(false);
	}
}

void Engine::Graphics::Effect::UnBind() const
{
	if (m_pShaderProgram != nullptr)
		m_pShaderProgram->release();
}

void Engine::Graphics::Effect::EnableAttributeArray(const int index)
{
	if (m_pShaderProgram != nullptr)
		m_pShaderProgram->enableAttributeArray(index);
}
                     
void Engine::Graphics::Effect::SetAttributeBuffer(const int location, const GLenum type, const int offset, const int tupleSize, const int stride)
{
	if (m_pShaderProgram != nullptr)
		m_pShaderProgram->setAttributeBuffer(location, type, offset, tupleSize, stride);
}

int Engine::Graphics::Effect::GetUniformLocation(const QString& name) const
{
	if (m_pShaderProgram != nullptr)
		return m_pShaderProgram->uniformLocation(name);

	return -1;
}

void Engine::Graphics::Effect::SetUniformValue(int location, GLint value)
{
	if (m_pShaderProgram != nullptr)
		return m_pShaderProgram->setUniformValue(location, value);
}

void Engine::Graphics::Effect::SetUniformValue(int location, const QVector3D & value)
{
	if (m_pShaderProgram != nullptr)
		return m_pShaderProgram->setUniformValue(location, value);
}

void Engine::Graphics::Effect::SetUniformValue(int location, const QVector4D & value)
{
	if (m_pShaderProgram != nullptr)
		return m_pShaderProgram->setUniformValue(location, value);
}

void Engine::Graphics::Effect::SetUniformValue(int location, const QMatrix4x4 & value)
{
	if (m_pShaderProgram != nullptr)
		return m_pShaderProgram->setUniformValue(location, value);
}

Engine::Graphics::Effect::Effect(const QString& vShaderName, const QString& fShaderName) : m_pShaderProgram(new QOpenGLShaderProgram)
{
	bool success = true;

	success = m_pShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, vShaderName);
	if (!success) assert(false);

	success = m_pShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, fShaderName);
	if (!success) assert(false);

	success = m_pShaderProgram->link();
	if (!success) assert(false);
}

Engine::Graphics::Effect::~Effect()
{
	if (m_pShaderProgram != nullptr)
		delete m_pShaderProgram;
}
