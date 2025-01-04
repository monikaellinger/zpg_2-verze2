#version 330

in vec4 ex_worldPos;
in vec3 ex_worldNorm;

out vec4 fragColor;

// Define the maximum number of lights and the Light struct
#define MAX_LIGHTS 4

struct Light {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
    vec4 color;
};

uniform int numberOfLights;

uniform vec3 viewPosition;
uniform vec4 objectColor; 

void main() {
    vec3 norm = normalize(ex_worldNorm);
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos));
    
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);  // Global ambient light
    vec4 totalDiffuse = vec4(0.0);

    for (int index = 0; index < numberOfLights; index++) {
        vec3 lightDir = normalize(vec3(lights[index].position) - vec3(ex_worldPos));
        vec3 reflectDir = reflect(-lightDir, norm);

        float diff = max(dot(lightDir, norm), 0.0);
         vec4 diffuseComponent = diff * lights[index].diffuse * lights[index].color * objectColor;

        totalDiffuse += diffuseComponent;
    }
    
    // Final color output including ambient, diffuse, and specular components
    fragColor = ambient + totalDiffuse;
}
