#pragma once

#include <QtCore\QString>
#include <QtGui\QOpenGLShaderProgram>

namespace Engine 
{
	namespace Graphics
	{
		class Effect
		{
		public:

			static bool Create(Effect*& o_effect, const QString& vShaderName, const QString& fShaderName);
			static bool Destroy(Effect*& o_effect);

			void Bind() const;
			void UnBind() const;
			void EnableAttributeArray(const int index);
			void SetAttributeBuffer(const int location, const GLenum type, const int offset, const int tupleSize, const int stride = 0);

			int GetUniformLocation(const QString& name) const;

			void SetUniformValue(int location, GLint value);
			void SetUniformValue(int location, const QVector3D& value);
			void SetUniformValue(int location, const QVector4D& value);
			void SetUniformValue(int location, const QMatrix4x4& value);

		private:

			QOpenGLShaderProgram* m_pShaderProgram;

			Effect(const QString& vShaderName, const QString& fShaderName);
			~Effect();
		};
	}
}