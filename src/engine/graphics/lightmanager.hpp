#ifndef ENGINE_GRAPHICS_LIGHTMANAGER_HPP
#define ENGINE_GRAPHICS_LIGHTMANAGER_HPP

#include "light.hpp"

namespace Engine{
namespace Graphics{

class LightManager{
    private:
        DirectionalLight dirLight;
        std::vector<PointLight> pointLights;
        bool hasDirectionalLight;
    public:
        LightManager();
        
        // Directional light methods
        void setDirectionalLight(const DirectionalLight& light);
        
        // Point light methods
        void addPointLight(const PointLight& light);
        void clearPointLights();
        void updatePointLight(int index, const PointLight& light);
        PointLight& setPointLight(int index){return pointLights[index];}
        
        // Apply all lights
        void applyAll(Shader& shader) const;
        

        
        // Getters
        DirectionalLight getDirectionalLight() const;
        int getPointLightCount() const;
        PointLight getPointLight(int index) const;
};
    
}}

#endif