#version 330 core

#define NR_POINT_LIGHTS 4

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

vec3 calcPointLight(PointLight pointlight, vec3 normal, vec3 fragPos, vec3 viewDir);

struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 calcDirLight(DirLight dirlight, vec3 normal, vec3 viewDir);

struct FlashLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

vec3 calcFlashLight(FlashLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

out vec4 FragColor;

// in vec3 color;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform int activePointLight;
uniform vec3 viewPos;
uniform Material material;

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirlight;
uniform FlashLight flashLight;

uniform bool useDirLight;
uniform bool usePointLight[NR_POINT_LIGHTS];
uniform bool useFlashLight;

void main()
{   
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.f);
    // phase 1: Directional lighting
    if(useDirLight){
        result = calcDirLight(dirlight, norm, viewDir);
    }
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        if(usePointLight[i]){
            result += calcPointLight(pointLights[i], norm, FragPos, viewDir);
        }
    }    
    // phase 3: Flashlight
    if(useFlashLight){
        result += calcFlashLight(flashLight, norm, FragPos, viewDir);    
    }
    
    FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight dirlight, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-dirlight.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = dirlight.ambient  * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse  = dirlight.diffuse  * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = dirlight.specular * spec * vec3(texture(material.specular, texCoord));
    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 calcFlashLight(FlashLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}