#include "lightmanager.hpp"
#include "light.hpp"
#include <MacTypes.h>
#include <cstddef>
#include <string>

Engine::Graphics::LightManager::LightManager()  : hasDirectionalLight(false){}

void Engine::Graphics::LightManager::setDirectionalLight(
    const DirectionalLight& light){
    dirLight = light;
    hasDirectionalLight = true;
}

void Engine::Graphics::LightManager::addPointLight(const PointLight& light){
    pointLights.push_back(light);
}

void Engine::Graphics::LightManager::clearPointLights(){
    pointLights.clear();
}

void Engine::Graphics::LightManager::updatePointLight(int index,
    const PointLight& light){
    pointLights[index] = light;
}

void Engine::Graphics::LightManager::applyAll(Shader& shader) const{
    if(hasDirectionalLight){
        dirLight.Apply(shader, "dirlight");
    }
    for(size_t i = 0; i < pointLights.size(); i++){
        std::string uniformName = "pointLights[" + std::to_string(i) + "]";
        pointLights[i].Apply(shader, uniformName);
    }
}

Engine::Graphics::DirectionalLight Engine::Graphics::LightManager::getDirectionalLight() const{
    return dirLight;
}

int Engine::Graphics::LightManager::getPointLightCount() const{
    return pointLights.size();
}

Engine::Graphics::PointLight Engine::Graphics::LightManager::getPointLight(int index) const{
    return pointLights[index];
}