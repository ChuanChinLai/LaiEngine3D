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
				enum class Type
				{
					Ambient, 
					Diffuse, 
					Specular, 
					Bump, 
				};

				unsigned int Id;
				Type Type;
				std::string Key;
			};
		}
	}
}