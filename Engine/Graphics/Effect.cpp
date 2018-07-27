#include "Effect.h"


#include <QtGui\QOpenGLFunctions> 
#include <QtGui\QOpenGLShaderProgram>

#include <iostream>
#include <cassert>

Engine::Graphics::Effect::Effect(QString vShaderName, QString fShaderName) : m_pShaderProgram(new QOpenGLShaderProgram)
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
