#pragma once

#include <string>

namespace Engine
{
	namespace Graphics
	{
		class Texture;

		namespace TextureFormats
		{
			struct sTexture
			{
				Texture* pTexture = nullptr;
				unsigned int ID;
				std::string Type;
				std::string Path;
			};
		}
	}
}