#version 330

in vec4 ex_worldPos;
in vec3 ex_worldNorm;

out vec4 fragColor;

// Define the maximum number of lights and the Light struct
#define MAX_LIGHTS 101

struct Light {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec3 viewPosition;
uniform vec4 objectColor; 

void main() {
    vec3 norm = normalize(ex_worldNorm);
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos));
    
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);  // Global ambient light
    vec4 totalDiffuse = vec4(0.0);
    vec4 totalSpecular = vec4(0.0);

    // Iterate over all active lights
    for (int index = 0; index < numberOfLights; index++) {
        vec3 lightDir = normalize(vec3(lights[index].position) - vec3(ex_worldPos));
        vec3 reflectDir = reflect(-lightDir, norm);

        // Calculate diffuse lighting
        float diff = max(dot(lightDir, norm), 0.0);
        
        // Calculate specular lighting
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

        // Accumulate diffuse and specular contributions
        totalDiffuse += diff * lights[index].diffuse * objectColor;
        totalSpecular += spec * lights[index].specular;
    }
    
    // Final color output including ambient, diffuse, and specular components
    fragColor = ambient + totalDiffuse + totalSpecular;
}
