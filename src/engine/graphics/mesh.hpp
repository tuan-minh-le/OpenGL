#ifndef ENGINE_GRAPHICS_MESH_HPP
#define ENGINE_GRAPHICS_MESH_HPP

#include "buffers/ebo.hpp"
#include "buffers/vbo.hpp"
#include "buffers/vao.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

using namespace Engine::Graphics::Buffers;

namespace Engine{
namespace Graphics{
    
// Struct for vertex data containing {position [x, y, z], texture mapping [0, 1], normal vector for lighting) [x, y, z]}
struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
    
    Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm)
        : position(pos), texCoords(tex), normal(norm) {}
    
    Vertex() 
        : position(0.0f), texCoords(0.0f), normal(0.0f, 0.0f, 1.0f) {}
};

class Mesh{
    private:
        VAO vao;
        VBO vbo;
        EBO ebo;
        
        std::vector<Vertex> vertices; 
        std::vector<GLuint> indices;
        bool hasIndices;
        
        void setupMesh(); // Handles buffer binding (VAO, VBO, EBO (if applicable))
    
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint> indices = {});
        void Draw(Shader& shader);
        static Mesh CreateCube(float size = 1.0f);
        ~Mesh();
};
}}


#endif