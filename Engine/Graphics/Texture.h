#pragma once

#include <QtCore\QString>
#include <QtGui\QOpenGLTexture>

namespace LaiEngine
{
	namespace Graphics
	{
		class Texture
		{
		public:

			static bool Create(Texture*& o_texture, const QString& imageName);
			static bool Destroy(Texture*& o_texture);

			void Bind();
			GLuint GetTextureId() const;

		private:

			QOpenGLTexture* m_pTexture;

			Texture(const QString& imageName);
			~Texture();
		};
	}
}