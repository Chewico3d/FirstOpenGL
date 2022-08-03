#include "IndexBuffer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : m_count(count)
{
	glGenBuffers(1, &BufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, data, GL_STATIC_DRAW);
	
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1,&BufferId);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
