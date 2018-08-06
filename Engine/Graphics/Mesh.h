#pragma once

#include "VertexFormats.h"

#include <vector>


class QOpenGLVertexArrayObject;
class QOpenGLBuffer;

namespace cy
{
	class TriMesh;
}


namespace Engine
{
	namespace Graphics
	{
		class Effect;
		class Texture;

		class Mesh
		{
		public:

            static bool Create(Mesh*& o_mesh, std::string objName);
			static bool Destroy(Mesh*& o_mesh);

			bool BindShader(Effect* effect);
			void Render();

		private:

			void InterpretObjData();
			std::vector<Engine::Graphics::VertexFormats::sMesh> InterpretVertexData();
			std::vector<Engine::Graphics::Texture*> InterpretTextureData();

			cy::TriMesh* m_pMesh;
			Effect* m_pEffect;

			QOpenGLVertexArrayObject* m_pVertexArrayObject;
			QOpenGLBuffer* m_pVertexBuffer;
			QOpenGLBuffer* m_pIndexBuffer;

			std::string m_directory;

			std::vector<VertexFormats::sMesh> m_vertices;
			std::vector<Engine::Graphics::Texture*> m_textures;
			std::vector<unsigned int> m_indices;

			Mesh();
			~Mesh();
		};
	}
}