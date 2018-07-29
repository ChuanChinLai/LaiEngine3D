#pragma once

#include "VertexFormats.h"
#include "TextureFormats.h"

#include <vector>

class QOpenGLVertexArrayObject;
class QOpenGLBuffer;

namespace Engine
{
	namespace Graphics
	{
		class Effect;

		class Mesh
		{
		public:

			Mesh(const std::vector<VertexFormats::sMesh>& vertices,
				 const std::vector<unsigned int>& indices, 
				 const std::vector<TextureFormats::sTexture>& textures);

			~Mesh();


			void Init(Effect* effect);
			void Render();
			void Destroy();


			std::vector<VertexFormats::sMesh> m_vertices;
			std::vector<unsigned int> m_indices;
			std::vector<TextureFormats::sTexture> m_textures;

		private:

			QOpenGLVertexArrayObject* m_pVertexArrayObject;
			QOpenGLBuffer* m_pVertexBuffer;
			QOpenGLBuffer* m_pIndexBuffer;

			Effect* m_pEffect;
		};
	}
}