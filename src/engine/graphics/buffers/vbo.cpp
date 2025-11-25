#include "vbo.hpp"

// Default constructor
Engine::Graphics::Buffers::VBO::VBO() : ID(0)
{
}

// Constructor that generates a Vertex Buffer Object and links it to vertices
Engine::Graphics::Buffers::VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Generic constructor for any vertex data type
Engine::Graphics::Buffers::VBO::VBO(const void* data, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

// Binds the VBO
void Engine::Graphics::Buffers::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void Engine::Graphics::Buffers::VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void Engine::Graphics::Buffers::VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}