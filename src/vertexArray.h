#pragma once

#include <vector>
#include <GL/glew.h>

#include "buffer.h"

namespace engine {

	class VertexArray {

	private:
		GLuint m_array;

	public:
		VertexArray();

		void append(Buffer* buffer, GLuint index);
	};
}