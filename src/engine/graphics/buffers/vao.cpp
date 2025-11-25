#include "vao.hpp"

// Constructor that generates a VAO ID
Engine::Graphics::Buffers::VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void Engine::Graphics::Buffers::VAO::LinkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void Engine::Graphics::Buffers::VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void Engine::Graphics::Buffers::VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void Engine::Graphics::Buffers::VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}