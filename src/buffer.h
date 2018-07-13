#pragma once

#include <GL/glew.h>

namespace engine {

	class Buffer {

	private:
		GLuint m_buffer;
		GLuint m_typeCount;

	public:
		Buffer(GLfloat* data, GLsizei length, GLuint typeCount);

		void bind() const;

		GLuint getTypeCount() const;
	};
}
