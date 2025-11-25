#ifndef ENGINE_GRAPHICS__BUFFERS_EBO_HPP
#define ENGINE_GRAPHICS__BUFFERS_EBO_HPP

#include <GL/glew.h>

namespace Engine{
namespace Graphics{
namespace Buffers{

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Default constructor
	EBO();
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);
	// Generic constructor for any index data type
	EBO(const void* data, GLsizeiptr size);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};
}}}

#endif
