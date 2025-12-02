#include "lightmanager.hpp"
#include "light.hpp"
#include <MacTypes.h>
#include <cstddef>
#include <string>

Engine::Graphics::LightManager::LightManager()  : hasDirectionalLight(false), useDirLight(false), useFlashLight(false){}

void Engine::Graphics::LightManager::setDirectionalLight(
    const DirectionalLight& light){
    dirLight = light;
    hasDirectionalLight = true;
    useDirLight = true;
}

void Engine::Graphics::LightManager::addPointLight(const PointLight& light){
    pointLights.push_back(light);
    usePointLight.push_back(true);
}

void Engine::Graphics::LightManager::clearPointLights(){
    pointLights.clear();
}

void Engine::Graphics::LightManager::updatePointLight(int index,
    const PointLight& light){
    pointLights[index] = light;
}

void Engine::Graphics::LightManager::setFlashLight(const FlashLight& light){
    flashLight = light;
    useFlashLight = true;
}

void Engine::Graphics::LightManager::applyAll(Shader& shader) const{
    if(hasDirectionalLight){
        dirLight.Apply(shader, "dirlight");
        shader.setBool("useDirLight", useDirLight);
    }
    for(size_t i = 0; i < pointLights.size(); i++){
        std::string uniformName = "pointLights[" + std::to_string(i) + "]";
        std::string boolName = "usePointLight[" + std::to_string(i) + "]";
        pointLights[i].Apply(shader, uniformName);
        shader.setBool(boolName, usePointLight[i]);
    }
    flashLight.Apply(shader, "flashLight");
    shader.setBool("useFlashLight", useFlashLight);
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

void Engine::Graphics::LightManager::setUseDirLight(bool value){
    useDirLight = value;
}

void Engine::Graphics::LightManager::setUseFlashLight(bool value){
    useFlashLight = value;
}

void Engine::Graphics::LightManager::setUsePointLight(int index, bool value){
    usePointLight[index] = value;
}

bool Engine::Graphics::LightManager::getUseDirLight() const{
    return useDirLight;
}

bool Engine::Graphics::LightManager::getUsePointLight(int index) const{
    return usePointLight[index];
}

bool Engine::Graphics::LightManager::getUseFlashLight() const{
    return useFlashLight;
}