#include "light.hpp"
#include <string>

/*
 * Abstract Light class implementation
 */
 
Engine::Graphics::Light::Light(glm::vec3 ambient, 
                            glm::vec3 diffuse,
                            glm::vec3 specular)
: ambient(ambient), diffuse(diffuse), specular(specular){}

void Engine::Graphics::Light::setAmbient(const glm::vec3& amb){
    ambient = amb;
}

void Engine::Graphics::Light::setDiffuse(const glm::vec3&diff){
    diffuse = diff;
}

void Engine::Graphics::Light::setSpecular(const glm::vec3& spec){
    specular = spec;
}

void Engine::Graphics::Light::setColor(const glm::vec3& color){
    ambient = color;
    diffuse = color;
    specular = color;
}

glm::vec3 Engine::Graphics::Light::getAmbient() const{
    return ambient;
}

glm::vec3 Engine::Graphics::Light::getDiffuse() const{
    return diffuse;
}

glm::vec3 Engine::Graphics::Light::getSpecular() const{
    return specular;
}

/*
 * Directional Light Class implementation
 */
 
 Engine::Graphics::DirectionalLight::DirectionalLight(
        glm::vec3 dir,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular
) : direction(dir), Light(ambient, diffuse, specular){}
 
void Engine::Graphics::DirectionalLight::Apply(Shader& shader, 
    const std::string& uniformName) const{
    shader.setVec3((uniformName + ".direction").c_str(), direction);
    shader.setVec3((uniformName + ".ambient").c_str(), ambient);
    shader.setVec3((uniformName + ".diffuse").c_str(), diffuse);
    shader.setVec3((uniformName + ".specular").c_str(), specular);
}

void Engine::Graphics::DirectionalLight::setDirection(const glm::vec3& dir){
    direction = dir;
}

glm::vec3 Engine::Graphics::DirectionalLight::getDirection() const{
    return direction;
}

/*
 * Point Light Class implementation
 */
 
 Engine::Graphics::PointLight::PointLight(
        glm::vec3 pos,
        float constant,
        float linear,
        float quadratic,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular)
: position(pos), constant(constant), linear(linear), quadratic(quadratic),
    Light(ambient, diffuse, specular){}
    
void Engine::Graphics::PointLight::Apply(Shader& shader, const std::string& uniformName) const{
    shader.setVec3((uniformName + ".position").c_str(), position);
    shader.setVec3((uniformName + ".ambient").c_str(), ambient);
    shader.setVec3((uniformName + ".diffuse").c_str(), diffuse);
    shader.setVec3((uniformName + ".specular").c_str(), specular);
    shader.setFloat((uniformName + ".constant").c_str(), constant);
    shader.setFloat((uniformName + ".linear").c_str(), linear);
    shader.setFloat((uniformName + ".quadratic").c_str(), quadratic);
}

void Engine::Graphics::PointLight::setPosition(const glm::vec3& pos){
    position = pos;
}

void Engine::Graphics::PointLight::setAttenuation(float c, float l, float q){
    constant = c;
    linear = l;
    quadratic = q;
}

glm::vec3 Engine::Graphics::PointLight::GetPosition() const{
    return position;
}