#include "Mesh.h"


#include <Engine\Graphics\Effect.h>

#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>

#include <iostream>

Engine::Graphics::Mesh::Mesh(const std::vector<VertexFormats::sMesh>& vertices, const std::vector<unsigned int>& indices, const std::vector<TextureFormats::sTexture>& textures)
{
	m_vertices = vertices;
	m_indices = indices;
	m_textures = textures;
}

Engine::Graphics::Mesh::~Mesh()
{
	Destroy();
}

void Engine::Graphics::Mesh::Init(Effect* effect)
{

	if (effect)
	{	
		m_pEffect = effect;
		m_pEffect->Bind();
	}
	else
	{
		std::cout << "ShaderProgram is nullptr" << std::endl;
		assert(false);
	}


	// Create Vertex Array Object
	{
		m_pVertexArrayObject = new QOpenGLVertexArrayObject();
		m_pVertexArrayObject->create();
		m_pVertexArrayObject->bind();
	}


	// Create Buffer (Do not release until VAO is created)
	{
		//Vertex Buffer
		{
			m_pVertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);

			if (!m_pVertexBuffer->create())
			{
				std::cout << "Create OpenGLBuffer Failed" << std::endl;
				assert(false);
			}

			if (!m_pVertexBuffer->bind())
			{
				std::cout << "Bind OpenGLBuffer Failed" << std::endl;
				assert(false);
			}
			m_pVertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
			m_pVertexBuffer->allocate(m_vertices.data(), static_cast<int>(sizeof(VertexFormats::sMesh) * m_vertices.size()));
		}

		//Index Buffer
		{
			m_pIndexBuffer = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);

			if (!m_pIndexBuffer->create())
			{
				std::cout << "Create OpenGLBuffer Failed" << std::endl;
				assert(false);
			}

			if (!m_pIndexBuffer->bind())
			{
				std::cout << "Bind OpenGLBuffer Failed" << std::endl;
				assert(false);
			}

			m_pIndexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
			m_pIndexBuffer->allocate(m_indices.data(), static_cast<int>(sizeof(GLuint) * m_indices.size()));
		}
	}

	//EnableAttribute: xyz
	{
		const int locationID = 0;
		m_pEffect->EnableAttributeArray(locationID);

		const GLenum dataType = GL_FLOAT;
		const int offset = 0;
		const int tupleSize = 3;
		const int stride = 32;

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}

	{
		//EnableAttribute: rgb
		const int locationID = 1;
		m_pEffect->EnableAttributeArray(locationID);

		const GLenum dataType = GL_FLOAT;
		const int offset = 12;
		const int tupleSize = 3;
		const int stride = 32;

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}


	{
		//EnableAttribute: uv
		const int locationID = 2;
		m_pEffect->EnableAttributeArray(locationID);

		const GLenum dataType = GL_FLOAT;
		const int offset = 24;
		const int tupleSize = 2;
		const int stride = 32;

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}

	m_pVertexArrayObject->release();
	m_pVertexBuffer->release();
	m_pIndexBuffer->release();

	m_pEffect->UnBind();
}

void Engine::Graphics::Mesh::Render()
{
	if (m_pEffect == nullptr)
	{
		std::cout << "ShaderProgram is nullptr" << std::endl;
		assert(false);
	}


	m_pEffect->Bind();

	{
		m_pVertexArrayObject->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		m_pVertexArrayObject->release();
	}

	m_pEffect->UnBind();
}

void Engine::Graphics::Mesh::Destroy()
{
	if (m_pVertexArrayObject)
	{
		m_pVertexArrayObject->destroy();
		delete m_pVertexArrayObject;
	}

	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->destroy();
		delete m_pVertexBuffer;
	}

	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->destroy();
		delete m_pIndexBuffer;
	}
}
