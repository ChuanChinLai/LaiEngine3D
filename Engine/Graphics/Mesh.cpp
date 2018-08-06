#include "Mesh.h"

#include <Engine\GameEngine\GLWidget.h>
#include <Engine\Graphics\Effect.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\Graphics\MeshLoader\cyTriMesh.h>

#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>

#include <iostream>

bool Engine::Graphics::Mesh::Create(Mesh*& o_mesh, std::string objName)
{
	if (o_mesh != nullptr)
		delete o_mesh;

	o_mesh = new Mesh();

	if (o_mesh == nullptr)
		return false;


	o_mesh->m_directory = objName.substr(0, objName.find_last_of('/'));

	o_mesh->m_pMesh = new cy::TriMesh();
	o_mesh->m_pMesh->LoadFromFileObj(objName.c_str());
	o_mesh->m_pMesh->ComputeNormals();

	o_mesh->InterpretObjData();


	return true;
}

bool Engine::Graphics::Mesh::Destroy(Mesh *& o_mesh)
{
	if (o_mesh != nullptr)
		delete o_mesh;

	return true;
}

bool Engine::Graphics::Mesh::BindShader(Effect* effect)
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
		return false;
	}

	// Create Vertex Array Object
	{
		if (m_pVertexArrayObject != nullptr)
		{
			m_pVertexArrayObject->destroy();
			delete m_pVertexArrayObject;
		}

		m_pVertexArrayObject = new QOpenGLVertexArrayObject();
		m_pVertexArrayObject->create();
		m_pVertexArrayObject->bind();
	}


	// Create Buffer (Do not release until VAO is created)
	{
		//Vertex Buffer
		{
			if (m_pVertexBuffer != nullptr)
			{
				m_pVertexBuffer->destroy();
				delete m_pVertexBuffer;
			}

			m_pVertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);

			if (!m_pVertexBuffer->create())
			{
				std::cout << "Create OpenGLBuffer Failed" << std::endl;
				assert(false);
				return false;
			}

			if (!m_pVertexBuffer->bind())
			{
				std::cout << "Bind OpenGLBuffer Failed" << std::endl;
				assert(false);
				return false;
			}
			m_pVertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
			m_pVertexBuffer->allocate(m_vertices.data(), static_cast<int>(sizeof(VertexFormats::sMesh) * m_vertices.size()));
		}

		//Index Buffer
		{
			if (m_pIndexBuffer != nullptr)
			{
				m_pIndexBuffer->destroy();
				delete m_pIndexBuffer;
			}

			m_pIndexBuffer = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);

			if (!m_pIndexBuffer->create())
			{
				std::cout << "Create OpenGLBuffer Failed" << std::endl;
				assert(false);
				return false;
			}

			if (!m_pIndexBuffer->bind())
			{
				std::cout << "Bind OpenGLBuffer Failed" << std::endl;
				assert(false);
				return false;
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
		const int stride = sizeof(Engine::Graphics::VertexFormats::sMesh);

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}

	//EnableAttribute: rgb
	{
		const int locationID = 1;
		m_pEffect->EnableAttributeArray(locationID);

		const GLenum dataType = GL_FLOAT;
		const int offset = 12;
		const int tupleSize = 3;
		const int stride = sizeof(Engine::Graphics::VertexFormats::sMesh);

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}


	{
		//EnableAttribute: uv
		const int locationID = 2;
		m_pEffect->EnableAttributeArray(locationID);

		const GLenum dataType = GL_FLOAT;
		const int offset = 24;
		const int tupleSize = 2;
		const int stride = sizeof(Engine::Graphics::VertexFormats::sMesh);

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}

	m_pVertexArrayObject->release();
	m_pVertexBuffer->release();
	m_pIndexBuffer->release();

	m_pEffect->UnBind();

	return true;
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

		QMatrix4x4 q;
		q.scale(QVector3D(0.1f, 0.1f, 0.1f));
		q.translate(QVector3D(0, -10.0f, 0));
		m_pEffect->SetUniformValue(m_pEffect->GetUniformLocation("Scale"), q);

		for (unsigned int i = 0; i < m_pMesh->NM(); i++)
		{
			const int pointsPerFace = 3;
			const int faceCount = m_pMesh->GetMaterialFaceCount(i);
			const int firstFace = m_pMesh->GetMaterialFirstFace(i);

			QOpenGLFunctions *pGLFunctions = QOpenGLContext::currentContext()->functions();
			pGLFunctions->glActiveTexture(static_cast<GLenum>(GL_TEXTURE0));

			m_pEffect->SetUniformValue(m_pEffect->GetUniformLocation("texture_diffuse1"), static_cast<GLint>(0));

			// and finally bind the texture
			pGLFunctions->glBindTexture(GL_TEXTURE_2D, m_textures[i]->GetTextureId());

			glDrawElements(GL_TRIANGLES, pointsPerFace * faceCount, GL_UNSIGNED_INT, (void*)(pointsPerFace * firstFace * sizeof(GLuint)));
		}

		m_pVertexArrayObject->release();
	}

	m_pEffect->UnBind();
}

void Engine::Graphics::Mesh::InterpretObjData()
{

//  m_indices made by InterpretVertexData();
	m_vertices = InterpretVertexData();
	m_textures = InterpretTextureData();
}

std::vector<Engine::Graphics::VertexFormats::sMesh> Engine::Graphics::Mesh::InterpretVertexData()
{
	std::vector<Engine::Graphics::VertexFormats::sMesh> vertexData(m_pMesh->NF());

	for (unsigned int i = 0; i < m_pMesh->NF(); i++)
	{
		const cy::TriMesh::TriFace  f = m_pMesh->F(i);
		const cy::TriMesh::TriFace nf = m_pMesh->FN(i);
		const cy::TriMesh::TriFace tf = m_pMesh->FT(i);

		//3 points in a face
		for (size_t j = 0; j < 3; j++)
		{
			const unsigned int index = f.v[j];

			m_indices.push_back(index);

			{
				const cy::Point3f& pos = m_pMesh->V(f.v[j]);
				vertexData[index].Position = QVector3D(pos.x, pos.y, pos.z);
			}

			{
				const cy::Point3f& nor = m_pMesh->VN(nf.v[j]);
				vertexData[index].Normal = QVector3D(nor.x, nor.y, nor.z);
			}

			{
				const cy::Point3f& uv = m_pMesh->VT(tf.v[j]);
				vertexData[index].UV = QVector3D(uv.x, uv.y, uv.z);
			}
		}
	}

	return vertexData;
}

std::vector<Engine::Graphics::Texture*> Engine::Graphics::Mesh::InterpretTextureData()
{
	std::vector<Engine::Graphics::Texture*> textureData(m_pMesh->NM(), nullptr);

	for (unsigned int i = 0; i < m_pMesh->NM(); i++)
	{
		const cy::TriMesh::Mtl& material = m_pMesh->M(i);

		if (material.map_Kd.data != nullptr)
		{
			std::string path = m_directory + "/" + material.map_Kd.data;

			Engine::Graphics::Texture* pTexture = nullptr;

			if (!Engine::Graphics::Texture::Create(pTexture, path.c_str()))
				assert(false);

			textureData[i] = pTexture;
		}
	}

	return textureData;
}

Engine::Graphics::Mesh::Mesh() : m_pVertexArrayObject(nullptr), m_pVertexBuffer(nullptr), m_pIndexBuffer(nullptr)
{

}


Engine::Graphics::Mesh::~Mesh()
{
	if (m_pMesh)
	{
		delete m_pMesh;
	}

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

	for (size_t i = 0; i < m_textures.size(); i++)
	{
		if (m_textures[i] != nullptr)
			Texture::Destroy(m_textures[i]);
	}

}