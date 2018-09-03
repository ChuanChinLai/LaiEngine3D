#include "Mesh.h"

#include <Engine\Graphics\Effect.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\GameEngine\GLWidget.h>

#include <External\cyCodeBase\cyTriMesh.h>

#include <QtGui\QOpenGLBuffer>
#include <QtGui\QOpenGLVertexArrayObject>

#include <iostream>

bool LaiEngine::Graphics::Mesh::Create(Mesh*& o_mesh, std::string objName)
{
	if (o_mesh != nullptr)
		Destroy(o_mesh);

	o_mesh = new Mesh();

	if (o_mesh == nullptr)
		return false;


	o_mesh->m_directory = objName.substr(0, objName.find_last_of('/'));

	o_mesh->m_pMeshLoader = new cy::TriMesh();
	o_mesh->m_pMeshLoader->LoadFromFileObj(objName.c_str());
	o_mesh->m_pMeshLoader->ComputeNormals();

	o_mesh->InterpretObjData();


	return true;
}

bool LaiEngine::Graphics::Mesh::Destroy(Mesh *& o_mesh)
{
	if (o_mesh != nullptr)
	{
		delete o_mesh;
		o_mesh = nullptr;
	}
	return true;
}

bool LaiEngine::Graphics::Mesh::BindShader(Effect* effect)
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

	//EnableAttribute: position
	{
		const int locationID = 0;
		m_pEffect->EnableAttributeArray(locationID);

		const GLenum dataType = GL_FLOAT;
		const int offset = 0;
		const int tupleSize = 3;
		const int stride = sizeof(LaiEngine::Graphics::VertexFormats::sMesh);

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}

	//EnableAttribute: normal vector
	{
		const int locationID = 1;
		m_pEffect->EnableAttributeArray(locationID);

		const GLenum dataType = GL_FLOAT;
		const int offset = 12;
		const int tupleSize = 3;
		const int stride = sizeof(LaiEngine::Graphics::VertexFormats::sMesh);

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}


	{
		//EnableAttribute: uv
		const int locationID = 2;
		m_pEffect->EnableAttributeArray(locationID);

		const GLenum dataType = GL_FLOAT;
		const int offset = 24;
		const int tupleSize = 2;
		const int stride = sizeof(LaiEngine::Graphics::VertexFormats::sMesh);

		m_pEffect->SetAttributeBuffer(locationID, dataType, offset, tupleSize, stride);
	}

	m_pVertexArrayObject->release();
	m_pVertexBuffer->release();
	m_pIndexBuffer->release();

	m_pEffect->UnBind();


	return true;
}

LaiEngine::Graphics::Effect* LaiEngine::Graphics::Mesh::GetShader() const
{
	return m_pEffect;
}

void LaiEngine::Graphics::Mesh::Render()
{
	if (m_pEffect == nullptr)
	{
		std::cout << "ShaderProgram is nullptr" << std::endl;
		assert(false);
	}

	m_pEffect->Bind();
	m_pVertexArrayObject->bind();

	if (m_pMeshLoader->NM() == 0)
	{
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, (void*)(0));
	}
	else
	{
		for (unsigned int i = 0; i < m_pMeshLoader->NM(); i++)
		{
			unsigned int ambientNr = 1;
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			unsigned int bumpNr = 1;

			for (size_t j = 0; j < m_texture_keys[i].size(); j++)
			{
				const TextureFormats::sTexture& tFormat = m_texture_keys[i][j];

				QOpenGLFunctions *pGLFunctions = QOpenGLContext::currentContext()->functions();

				pGLFunctions->glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + j));

				std::string textureNameInShader;

				if (tFormat.Type == TextureFormats::sTexture::Type::Ambient)
					textureNameInShader = "Ambient" + std::to_string(ambientNr++);
				else if (tFormat.Type == TextureFormats::sTexture::Type::Diffuse)
					textureNameInShader = "Diffuse" + std::to_string(diffuseNr++);
				else if (tFormat.Type == TextureFormats::sTexture::Type::Specular)
					textureNameInShader = "Specular" + std::to_string(specularNr++);
				else if (tFormat.Type == TextureFormats::sTexture::Type::Bump)
					textureNameInShader = "Bump" + std::to_string(bumpNr++);


				m_pEffect->SetUniformValue(m_pEffect->GetUniformLocation(textureNameInShader.c_str()), static_cast<GLint>(j));

				pGLFunctions->glBindTexture(GL_TEXTURE_2D, tFormat.Id);
			}

			const int pointsPerFace = 3;
			const int faceCount = m_pMeshLoader->GetMaterialFaceCount(i);
			const int firstFace = m_pMeshLoader->GetMaterialFirstFace(i);

			glDrawElements(GL_TRIANGLES, pointsPerFace * faceCount, GL_UNSIGNED_INT, (void*)(pointsPerFace * firstFace * sizeof(GLuint)));
		}
	}

	m_pVertexArrayObject->release();
	m_pEffect->UnBind();
}

void LaiEngine::Graphics::Mesh::InterpretObjData()
{
//  m_indices made by InterpretVertexData();
	InterpretVertexData();
	InterpretTextureData();
}

void LaiEngine::Graphics::Mesh::InterpretVertexData()
{

	std::vector<LaiEngine::Graphics::VertexFormats::sMesh> vertexData(m_pMeshLoader->NV());

	for (unsigned int i = 0; i < m_pMeshLoader->NF(); i++)
	{
		const cy::TriMesh::TriFace  f = m_pMeshLoader->F(i);
		const cy::TriMesh::TriFace nf = m_pMeshLoader->FN(i);
		const cy::TriMesh::TriFace tf = m_pMeshLoader->FT(i);

		//3 points in a face
		for (size_t j = 0; j < 3; j++)
		{
			const unsigned int index = f.v[j];

			m_indices.push_back(index);

			LaiEngine::Graphics::VertexFormats::sMesh vertex;

			{
				const cy::Point3f& pos = m_pMeshLoader->V(f.v[j]);
				vertexData[index].Position = QVector3D(pos.x, pos.y, pos.z);
			}

			{
				const cy::Point3f& nor = m_pMeshLoader->VN(nf.v[j]);
				vertexData[index].Normal = QVector3D(nor.x, nor.y, nor.z);
			}

			{
				const cy::Point3f& uv = m_pMeshLoader->VT(tf.v[j]);
				vertexData[index].UV = QVector3D(uv.x, uv.y, uv.z);
			}
		}
	}

	m_vertices = vertexData;
}

void LaiEngine::Graphics::Mesh::InterpretTextureData()
{
	TextureFormats::sTexture tFormat;

	for (unsigned int i = 0; i < m_pMeshLoader->NM(); i++)
	{
		const cy::TriMesh::Mtl& material = m_pMeshLoader->M(i);

		if (material.map_Ka.data != nullptr)
		{
			std::string texturePath = m_directory + "/" + material.map_Ka.data;

			tFormat.Id = GetTextureByName(texturePath)->GetTextureId();
			tFormat.Key = texturePath;
			tFormat.Type = TextureFormats::sTexture::Type::Ambient;

			m_texture_keys[i].push_back(tFormat);
		}

		if (material.map_Kd.data != nullptr)
		{
			std::string texturePath = m_directory + "/" + material.map_Kd.data;

			tFormat.Id = GetTextureByName(texturePath)->GetTextureId();
			tFormat.Key = texturePath;
			tFormat.Type = TextureFormats::sTexture::Type::Diffuse;

			m_texture_keys[i].push_back(tFormat);
		}

		if (material.map_Ks.data != nullptr)
		{
			std::string texturePath = m_directory + "/" + material.map_Ks.data;

			tFormat.Id = GetTextureByName(texturePath)->GetTextureId();
			tFormat.Key = texturePath;
			tFormat.Type = TextureFormats::sTexture::Type::Specular;

			m_texture_keys[i].push_back(tFormat);
		}

		if (material.map_bump.data != nullptr)
		{
			std::string texturePath = m_directory + "/" + material.map_bump.data;

			tFormat.Id = GetTextureByName(texturePath)->GetTextureId();
			tFormat.Key = texturePath;
			tFormat.Type = TextureFormats::sTexture::Type::Bump;

			m_texture_keys[i].push_back(tFormat);
		}
	}
}

LaiEngine::Graphics::Texture* LaiEngine::Graphics::Mesh::GetTextureByName(const std::string& texturePath)
{
	if (m_textures.count(texturePath) == 0)
	{
		LaiEngine::Graphics::Texture* pTexture = nullptr;

		if (!LaiEngine::Graphics::Texture::Create(pTexture, texturePath.c_str()))
			assert(false);

		m_textures[texturePath] = pTexture;
	}

	return m_textures[texturePath];
}

LaiEngine::Graphics::Mesh::Mesh() : m_pVertexArrayObject(nullptr), m_pVertexBuffer(nullptr), m_pIndexBuffer(nullptr)
{

}


LaiEngine::Graphics::Mesh::~Mesh()
{
	if (m_pMeshLoader)
	{
		delete m_pMeshLoader;
		m_pMeshLoader = nullptr;
	}

	if (m_pVertexArrayObject)
	{
		m_pVertexArrayObject->destroy();
		delete m_pVertexArrayObject;
		m_pVertexArrayObject = nullptr;
	}

	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->destroy();
		delete m_pVertexBuffer;
		m_pVertexBuffer = nullptr;
	}

	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->destroy();
		delete m_pIndexBuffer;
		m_pIndexBuffer = nullptr;
	}

	for (auto& texture : m_textures)
	{
		if (texture.second != nullptr)
		{
			Texture::Destroy(texture.second);
		}
	}

	m_textures.clear();
}