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

			Effect(QString vShaderName, QString fShaderName);
			~Effect();

			void Bind() const;
			void UnBind() const;
			void EnableAttributeArray(const int index);
			void SetAttributeBuffer(const int location, const GLenum type, const int offset, const int tupleSize, const int stride = 0);

			int GetUniformLocation(const QString& name) const;
			void SetUniformValue(int location, GLint value);

		private:

			QOpenGLShaderProgram* m_pShaderProgram;
		};
	}
}