#ifndef ENGINE_GRAPHICS_LIGHTMANAGER_HPP
#define ENGINE_GRAPHICS_LIGHTMANAGER_HPP

#include "light.hpp"

namespace Engine{
namespace Graphics{

class LightManager{
    private:
        DirectionalLight dirLight;
        std::vector<PointLight> pointLights;
        FlashLight flashLight;
        
        bool hasDirectionalLight;

        bool useDirLight;
        std::vector<unsigned char> usePointLight;
        bool useFlashLight;
    public:
        LightManager();

        // Directional light methods
        void setDirectionalLight(const DirectionalLight& light);

        // Point light methods
        void addPointLight(const PointLight& light);
        void clearPointLights();
        void updatePointLight(int index, const PointLight& light);
        PointLight& setPointLight(int index){return pointLights[index];}
        
        // FlashLight methods
        void setFlashLight(const FlashLight& light);
        FlashLight& setFlashLight(){ return flashLight;}
        
        // Apply all lights
        void applyAll(Shader& shader) const;

        // Setters
        void setUsePointLight(int index, bool value);
        void setUseDirLight(bool value);
        void setUseFlashLight(bool value);

        bool* setUseDirLight(){return &useDirLight;}
        unsigned char* setUsePointLight(int index){return &usePointLight[index];}
        bool* setUseFlashLight(){return &useFlashLight;};


        // Getters
        DirectionalLight getDirectionalLight() const;
        int getPointLightCount() const;
        PointLight getPointLight(int index) const;
        FlashLight getFlashLight() const;
        
        bool getUsePointLight(int index) const;
        bool getUseDirLight() const;
        bool getUseFlashLight() const;
};

}}

#endif
