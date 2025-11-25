#include "ebo.hpp"

// Constructor that generates a Elements Buffer Object and links it to indices
Engine::Graphics::Buffers::EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds the EBO
void Engine::Graphics::Buffers::EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void Engine::Graphics::Buffers::EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void Engine::Graphics::Buffers::EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}