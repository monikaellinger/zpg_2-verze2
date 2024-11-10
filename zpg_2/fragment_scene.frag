#version 330 core

#define MAX_LIGHTS 4

struct Light {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPosition;
uniform vec4 objectColor;

in vec3 FragPos;
in vec3 Normal;

out vec4 fragColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPosition - FragPos);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * objectColor;

    vec4 result = ambient;

    for (int i = 0; i < numberOfLights; i++) {
        vec3 lightDir = normalize(vec3(lights[i].position) - FragPos);
        
        // Diffuse lighting
        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = diff * lights[i].diffuse * objectColor;

        // Specular lighting
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec4 specular = spec * lights[i].specular;

        // Accumulate all lighting effects
        result += diffuse + specular;
    }
    
    fragColor = result;
}
