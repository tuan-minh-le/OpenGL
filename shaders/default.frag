#version 330 core
out vec4 FragColor;

// in vec3 color;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;  

uniform sampler2D tex0;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{   
    // Ambient lighting
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular Lighting
    float specularStrength = 0.5;
    int shininess = 16;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;  
    
    vec4 texColor = texture(tex0, texCoord);
    FragColor = (vec4(ambient, 1.0) + vec4(diffuse, 1.0) + vec4(specular, 1.0)) * texColor;
}
