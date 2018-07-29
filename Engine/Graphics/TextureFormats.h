#pragma once

#include <string>

namespace Engine
{
	namespace Graphics
	{
		namespace TextureFormats
		{
			struct sTexture
			{
				unsigned int ID;
				std::string Type;
				std::string Path;
			};
		}
	}
}