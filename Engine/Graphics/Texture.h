#pragma once

#include <QtCore\QString>

class QOpenGLTexture;

namespace Engine
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture(QString imageName);
			~Texture();

			void Bind();

		private:

			QOpenGLTexture* pTexture;
		};
	}
}