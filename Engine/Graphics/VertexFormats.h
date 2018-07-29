#pragma once

#include <QtGui\QVector2D>
#include <QtGui\QVector3D>

namespace Engine
{
	namespace Graphics
	{
		namespace VertexFormats
		{
			struct sSprite
			{
				float x, y;
				float u, v;
			};


			struct sMesh
			{
				QVector3D Position;
				QVector3D Normal;
				QVector2D UV;
//				QVector3D Tangent;
//				QVector3D Bitangent;
			};
		}
	}
}