#ifndef ENGINE_GRAPHICS_TEXTURE_HPP
#define ENGINE_GRAPHICS_TEXTURE_HPP

#include <GL/glew.h>
#include <stb_image/stb_image.h>

#include "shader.hpp"

namespace Engine{
namespace Graphics{

class Texture
{
public:
   GLuint ID;
   GLenum type;
   Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

   // Assigns a texture unit to a texture
   void texUnit(Shader &shader, const char *uniform, GLuint unit);
   // Binds a texture
   void Bind();
   // Unbinds a texture
   void Unbind();
   // Deletes a texture
   void Delete();
};
}}
#endif