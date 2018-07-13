#include "vertexArray.h"
#include <iostream>
using namespace engine;

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_array);
}

void VertexArray::append(Buffer* buffer, GLuint index) {
	glBindVertexArray(m_array);
	buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getTypeCount(), GL_FLOAT, GL_FALSE, 0, 0);
}
