#include "Texture.h"


bool Engine::Graphics::Texture::Create(Texture *& o_texture, const QString & imageName)
{
	if (o_texture != nullptr)
		delete o_texture;

	o_texture = new Texture(imageName);

	return true;
}

bool Engine::Graphics::Texture::Destroy(Texture *& o_texture)
{
	if (o_texture != nullptr) 
		delete o_texture;

	return true;
}

void Engine::Graphics::Texture::Bind()
{
	if (m_pTexture != nullptr)
		m_pTexture->bind();
}

GLuint Engine::Graphics::Texture::GetTextureId() const
{
	return m_pTexture->textureId();
}

Engine::Graphics::Texture::Texture(const QString& imageName) : m_pTexture(new QOpenGLTexture(QImage(imageName).mirrored()))
{
	if (m_pTexture == nullptr)
		assert(false);
}

Engine::Graphics::Texture::~Texture()
{
	if (m_pTexture != nullptr)
		delete m_pTexture;
}