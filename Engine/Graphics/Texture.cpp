#include "Texture.h"

#include <QtGui\QOpenGLTexture>

Engine::Graphics::Texture::Texture(QString imageName)
{
	pTexture = new QOpenGLTexture(QImage(imageName).mirrored());
}

Engine::Graphics::Texture::~Texture()
{
	if (pTexture != nullptr)
		delete pTexture;
}

void Engine::Graphics::Texture::Bind()
{
	if (pTexture != nullptr)
		pTexture->bind();
}
