#ifndef ENGINE_GRAPHICS__BUFFERS_VBO_HPP
#define ENGINE_GRAPHICS__BUFFERS_VBO_HPP

#include <GL/glew.h>

namespace Engine{
namespace Graphics{
namespace Buffers{

class VBO
{
public:
   // Reference ID of the Vertex Buffer Object
   GLuint ID;
   // Default constructor
   VBO();
   // Constructor that generates a Vertex Buffer Object and links it to vertices
   VBO(GLfloat *vertices, GLsizeiptr size);
   // Generic constructor for any vertex data type
   VBO(const void* data, GLsizeiptr size);

   // Binds the VBO
   void Bind();
   // Unbinds the VBO
   void Unbind();
   // Deletes the VBO
   void Delete();
};
}}}

#endif
