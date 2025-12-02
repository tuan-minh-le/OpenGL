#ifndef ENGINE_GRAPHICS_LIGHT_HPP
#define ENGINE_GRAPHICS_LIGHT_HPP

#include <glm/glm.hpp>
#include <string>
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "shader.hpp"

namespace Engine{
namespace Graphics{

class Light{
    // Every light has an ambient, diffuse, specular component
    protected:
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    
    public:
        Light(glm::vec3 ambient = glm::vec3(1.f, 1.f, 1.f),
            glm::vec3 diffuse = glm::vec3(1.f, 1.f, 1.f),
            glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f));
        
        virtual ~Light() = default;
        
        // Abstract method to apply light to shader for each lighting method
        virtual void Apply(Shader& shader, const std::string& uniformName) const = 0;
        
        // Setters
        void setAmbient(const glm::vec3& amb);
        void setDiffuse(const glm::vec3& diff);
        void setSpecular(const glm::vec3& spec);
        void setColor(const glm::vec3& color);
        
        // Getters
        glm::vec3 getAmbient() const;
        glm::vec3 getDiffuse() const;
        glm::vec3 getSpecular() const;
};

class DirectionalLight : public Light{
    private: 
        glm::vec3 direction;
    
    public:
        DirectionalLight(glm::vec3 dir = glm::vec3(-0.2f, -1.0f, -0.3f),
                glm::vec3 ambient = glm::vec3(1.f, 1.f, 1.f),
                glm::vec3 diffuse = glm::vec3(1.f, 1.f, 1.f),
                glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f));
        
        void Apply(Shader& shader, const std::string& uniformName) const override;
        
        void setDirection(const glm::vec3& dir);
        glm::vec3 getDirection() const;
};

class PointLight : public Light{
    protected:
        glm::vec3 position;
        float constant;
        float linear;
        float quadratic;
    
    public:
        PointLight(glm::vec3 pos = glm::vec3(0.f),
                float constant = 1.f,
                float linear = 0.09f,
                float quadratic = 0.032f,
                glm::vec3 ambient = glm::vec3(1.f, 1.f, 1.f),
                glm::vec3 diffuse = glm::vec3(1.f, 1.f, 1.f),
                glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f));
        
        void Apply(Shader& shader, const std::string& uniformName) const override;
        
        // Setters
        void setPosition(const glm::vec3& pos);
        void setAttenuation(float c, float l, float q);
        
        glm::vec3 GetPosition() const;
};

class FlashLight : public PointLight{
    private:
       glm::vec3 direction;
       float cutOff;
       float outerCutOff;
    
    public:
        FlashLight(glm::vec3 direction = glm::vec3(2, -2, -5),
                float cutOff = glm::cos(glm::radians(12.5f)),
                float outerCutOff = glm::cos(glm::radians(15.f)),
                glm::vec3 pos = glm::vec3(0.f),
                float constant = 1.f,
                float linear = 0.09f,
                float quadratic = 0.032f,
                glm::vec3 ambient = glm::vec3(1.f, 1.f, 1.f),
                glm::vec3 diffuse = glm::vec3(1.f, 1.f, 1.f),
                glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f));
        
        FlashLight(glm::vec3 pos, glm::vec3 dir);
        
        void Apply(Shader& shader, const std::string& uniformName) const override;
        
        void setDirection(const glm::vec3& dir);
        void setCutOff(float cutO, float outerCutO);
        
        glm::vec3 getDirection() const;
}; 

}}

#endif