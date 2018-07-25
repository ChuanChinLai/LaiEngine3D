#include "Effect.h"

#include <iostream>
#include <cassert>

Engine::Graphics::Effect::Effect(QString vShaderName, QString fShaderName) : m_program(new QOpenGLShaderProgram)
{
	bool success = true;

	success = m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vShaderName);
	if (!success) assert(false);

	success = m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fShaderName);
	if (!success) assert(false);

	success = m_program->link();
	if (!success) assert(false);
}

Engine::Graphics::Effect::~Effect()
{
	if (m_program != nullptr)
		delete m_program;
}

void Engine::Graphics::Effect::Bind() const
{
	if (m_program != nullptr)
	{
		bool success = m_program->bind();
		if (!success) assert(false);
	}
}

void Engine::Graphics::Effect::UnBind() const
{
	if (m_program != nullptr)
		m_program->release();
}

void Engine::Graphics::Effect::EnableAttributeArray(const int index)
{
	if (m_program != nullptr)
		m_program->enableAttributeArray(index);
}
                     
void Engine::Graphics::Effect::SetAttributeBuffer(const int location, const GLenum type, const int offset, const int tupleSize, const int stride)
{
	if (m_program != nullptr)
		m_program->setAttributeBuffer(location, type, offset, tupleSize, stride);
}
