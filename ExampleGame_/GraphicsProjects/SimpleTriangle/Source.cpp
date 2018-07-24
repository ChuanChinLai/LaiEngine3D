#include "Header.h"

#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>
#include <QtGui\QOpenGLShaderProgram>

#include <iostream>

// Create a colored triangle
static const float sg_vertexes[] = { 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                                     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
                                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
                                    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f };


static const unsigned int sg_indices[] = { 0, 3, 1, 1, 3, 2 };



SimpleTriangle::SimpleTriangle()
{

}

SimpleTriangle::~SimpleTriangle()
{
	Destroy();
}

bool SimpleTriangle::Init()
{

	{
		// Create Shader (Do not release until VAO is created)
		m_program = new QOpenGLShaderProgram();
		m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "Assets/shaders/simple.vert");
		m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "Assets/shaders/simple.frag");
		m_program->link();
		m_program->bind();
	}

	{
		// Create Vertex Array Object
		m_object = new QOpenGLVertexArrayObject();
		m_object->create();
		m_object->bind();
	}

	{
		// Create Buffer (Do not release until VAO is created)
		m_vertex = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);

		if (!m_vertex->create())
		{
			std::cout << "Create OpenGLBuffer Failed" << std::endl;
			assert(false);
		}

		if (!m_vertex->bind())
		{
			std::cout << "Bind OpenGLBuffer Failed" << std::endl;
			assert(false);
		}
		m_vertex->setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_vertex->allocate(sg_vertexes, sizeof(sg_vertexes));
	}

	{
		m_index = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);

		if (!m_index->create())
		{
			std::cout << "Create OpenGLBuffer Failed" << std::endl;
			assert(false);
		}

		if (!m_index->bind())
		{
			std::cout << "Bind OpenGLBuffer Failed" << std::endl;
			assert(false);
		}

		m_index->setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_index->allocate(sg_indices, sizeof(sg_indices));
	}


	m_program->enableAttributeArray(0);
	m_program->enableAttributeArray(1);

	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 24);
	m_program->setAttributeBuffer(1, GL_FLOAT, 12, 3, 24);

	// Release (unbind) all
	m_object->release();
	m_vertex->release();
	m_index->release();
	m_program->release();

	return true;
}

void SimpleTriangle::Update()
{
	m_program->bind();
	{
		m_object->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		m_object->release();
	}
	m_program->release();
}

bool SimpleTriangle::Destroy()
{
	if (m_object != nullptr)
	{
		m_object->destroy();
		delete m_object;
	}

	if (m_program != nullptr)
	{
		delete m_program;
	}

	if (m_vertex != nullptr)
	{
		m_vertex->destroy();
		delete m_vertex;
	}

	if (m_index != nullptr)
	{
		m_index->destroy();
		delete m_index;
	}

	return true;
}

