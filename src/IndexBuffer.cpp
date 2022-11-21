#include "VertexBuffer.h";
#include "Renderer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLLOGCALL(glGenBuffers(1, &m_RendererID));
	GLLOGCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLLOGCALL(glBufferData(GL_ARRAY_BUFFER, size , data, GL_STATIC_DRAW));
	//GLLOGCALL(glEnableVertexAttribArray(0));
	//GLLOGCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
}

VertexBuffer::~VertexBuffer()
{
	GLLOGCALL(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::bind()
{
	GLLOGCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unbind()
{
	GLLOGCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

}
