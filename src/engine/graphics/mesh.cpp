#include "mesh.hpp"
#include "buffers/ebo.hpp"
#include <cstddef>
#include <vector>

Engine::Graphics::Mesh::Mesh(const std::vector<Vertex>& vertices, 
    const std::vector<GLuint> indices)
    : vertices(vertices), indices(indices){
        hasIndices = !indices.empty();
        setupMesh();
}

Engine::Graphics::Mesh::~Mesh(){
    vbo.Delete();
    ebo.Delete();
    vao.Delete();
}
    

void Engine::Graphics::Mesh::setupMesh(){
    vao.Bind();
    vbo = VBO(vertices.data(), vertices.size() * sizeof(Vertex));
    if(hasIndices){
        ebo = EBO(indices.data(), indices.size() * sizeof(GLuint));
    }
    // Position
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    // Texture Coordinates
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    // Normal
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    
    vao.Unbind();
}

void Engine::Graphics::Mesh::Draw(Shader& shader){
    shader.Activate();
    vao.Bind();
    
    if(hasIndices){
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    else{
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
    
    vao.Unbind();
}

Engine::Graphics::Mesh Engine::Graphics::Mesh::CreateCube(float size) {
    float halfSize = size / 2.0f;
    
    std::vector<Vertex> vertices;
    
    // Front face
    vertices.push_back({{-halfSize, -halfSize,  halfSize}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
    vertices.push_back({{ halfSize, -halfSize,  halfSize}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
    vertices.push_back({{ halfSize,  halfSize,  halfSize}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}});
    vertices.push_back({{ halfSize,  halfSize,  halfSize}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}});
    vertices.push_back({{-halfSize,  halfSize,  halfSize}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}});
    vertices.push_back({{-halfSize, -halfSize,  halfSize}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
    
    // Back face
    vertices.push_back({{-halfSize, -halfSize, -halfSize}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}});
    vertices.push_back({{-halfSize,  halfSize, -halfSize}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}});
    vertices.push_back({{ halfSize,  halfSize, -halfSize}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}});
    vertices.push_back({{ halfSize,  halfSize, -halfSize}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}});
    vertices.push_back({{ halfSize, -halfSize, -halfSize}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}});
    vertices.push_back({{-halfSize, -halfSize, -halfSize}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}});
    
    // Left face
    vertices.push_back({{-halfSize,  halfSize,  halfSize}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}});
    vertices.push_back({{-halfSize,  halfSize, -halfSize}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}});
    vertices.push_back({{-halfSize, -halfSize, -halfSize}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}});
    vertices.push_back({{-halfSize, -halfSize, -halfSize}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}});
    vertices.push_back({{-halfSize, -halfSize,  halfSize}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}});
    vertices.push_back({{-halfSize,  halfSize,  halfSize}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}});
    
    // Right face
    vertices.push_back({{ halfSize,  halfSize,  halfSize}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
    vertices.push_back({{ halfSize, -halfSize, -halfSize}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    vertices.push_back({{ halfSize,  halfSize, -halfSize}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    vertices.push_back({{ halfSize, -halfSize, -halfSize}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    vertices.push_back({{ halfSize,  halfSize,  halfSize}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
    vertices.push_back({{ halfSize, -halfSize,  halfSize}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
    
    // Bottom face
    vertices.push_back({{-halfSize, -halfSize, -halfSize}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}});
    vertices.push_back({{ halfSize, -halfSize, -halfSize}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}});
    vertices.push_back({{ halfSize, -halfSize,  halfSize}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}});
    vertices.push_back({{ halfSize, -halfSize,  halfSize}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}});
    vertices.push_back({{-halfSize, -halfSize,  halfSize}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}});
    vertices.push_back({{-halfSize, -halfSize, -halfSize}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}});
    
    // Top face
    vertices.push_back({{-halfSize,  halfSize, -halfSize}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}});
    vertices.push_back({{-halfSize,  halfSize,  halfSize}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
    vertices.push_back({{ halfSize,  halfSize,  halfSize}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
    vertices.push_back({{ halfSize,  halfSize,  halfSize}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
    vertices.push_back({{ halfSize,  halfSize, -halfSize}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}});
    vertices.push_back({{-halfSize,  halfSize, -halfSize}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}});
    
    return Mesh(vertices);  // No indices needed - using triangles directly
}