#pragma once

#include "VertexFormats.h"
#include "TextureFormats.h"

#include <vector>
#include <unordered_map>


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

			void InterpretVertexData();
			void InterpretTextureData();

			Texture* GetTextureByName(const std::string& texturePath);

			cy::TriMesh* m_pMeshLoader;
			Effect* m_pEffect;

			QOpenGLVertexArrayObject* m_pVertexArrayObject;
			QOpenGLBuffer* m_pVertexBuffer;
			QOpenGLBuffer* m_pIndexBuffer;

			std::string m_directory;

			std::vector<VertexFormats::sMesh> m_vertices;
			std::unordered_map<std::string, Engine::Graphics::Texture*> m_textures;
			std::vector<unsigned int> m_indices;
			
			std::unordered_map<unsigned int, std::vector<TextureFormats::sTexture>> m_texture_keys;

			Mesh();
			~Mesh();
		};
	}
}