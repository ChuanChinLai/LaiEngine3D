#include "Texture.h"


bool LaiEngine::Graphics::Texture::Create(Texture *& o_texture, const QString & imageName)
{
	if (o_texture != nullptr)
		Destroy(o_texture);

	o_texture = new Texture(imageName);

	return true;
}

bool LaiEngine::Graphics::Texture::Destroy(Texture *& o_texture)
{
	if (o_texture != nullptr)
	{
		delete o_texture;
		o_texture = nullptr;
	}
	return true;
}

void LaiEngine::Graphics::Texture::Bind()
{
	if (m_pTexture != nullptr)
		m_pTexture->bind();
}

GLuint LaiEngine::Graphics::Texture::GetTextureId() const
{
	return m_pTexture->textureId();
}

LaiEngine::Graphics::Texture::Texture(const QString& imageName) : m_pTexture(new QOpenGLTexture(QImage(imageName).mirrored()))
{
	if (m_pTexture == nullptr)
		assert(false);
}

LaiEngine::Graphics::Texture::~Texture()
{
	if (m_pTexture != nullptr)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}