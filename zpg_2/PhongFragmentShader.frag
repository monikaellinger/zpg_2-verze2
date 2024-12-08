#version 330

in vec4 ex_worldPos;        // World position from vertex shader
in vec3 ex_worldNorm;       // World normal from vertex shader
in vec2 ex_texCoords;       // Texture coordinates from vertex shader

out vec4 fragColor;

uniform sampler2D textureSampler; // The texture sampler
uniform vec3 viewPosition;        // Camera position
uniform vec4 objectColor;         // Base object color

// Lighting constants
struct Light {
    vec4 position;      // Light position (can be directional for directional lights)
    vec4 diffuse;       // Diffuse color of the light
    vec4 specular;      // Specular color of the light
    vec4 color;         // Ambient color of the light
    vec3 direction;     // Direction of the light (used for directional and spot lights)
    float cutoff;       // Spotlight cutoff (cosine of angle)
    float outerCutoff;  // Outer cutoff (soft transition for spotlights)
};

uniform Light lights[10];  // Array of lights
uniform int numberOfLights;  // Number of lights in the scene

// Calculate lighting for each light source
vec4 calculateLight(Light light, vec3 norm, vec3 viewDir, vec3 fragPos, vec4 texColor) {
    vec4 ambient = light.color * texColor * 0.1;  // Ambient lighting contribution
    vec4 diffuse = vec4(0.0);                     // Diffuse lighting contribution
    vec4 specular = vec4(0.0);                    // Specular lighting contribution

    // Point light
    if (light.position.w == 1.0) {
        vec3 lightDir = normalize(vec3(light.position) - fragPos);  // Direction to light
        if (dot(norm, lightDir) > 0.0) {
            float diff = max(dot(norm, lightDir), 0.0);  // Diffuse factor

            // Specular reflection
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Phong model

            diffuse = diff * light.diffuse * texColor * light.color * objectColor;
            specular = spec * light.specular * light.color;
        }
    }
    // Directional light (for sunlight, etc.)
    else if (light.position.w == 0.0) {
        vec3 lightDir = normalize(light.direction);  // Direction for directional light
        if (dot(norm, lightDir) > 0.0) {
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

            diffuse = diff * light.diffuse * texColor * light.color * objectColor;
            specular = spec * light.specular * light.color;
        }
    }
    // Spotlight
    else if (light.position.w == 2.0) {
        vec3 lightDir = normalize(vec3(light.position) - fragPos);
        float theta = dot(lightDir, normalize(light.direction));  // Angle with spotlight direction
        float epsilon = light.cutoff - light.outerCutoff;
        float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

        if (theta > light.outerCutoff && dot(norm, lightDir) > 0.0) {
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

            diffuse = diff * light.diffuse * texColor * light.color * objectColor * intensity;
            specular = spec * light.specular * light.color * intensity;
        }
    }

    // Combine ambient, diffuse, and specular components
    return ambient + diffuse + specular;
}

void main() {
    vec3 norm = normalize(ex_worldNorm);  // Normalize the normal
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos));  // View direction
    vec3 fragPos = vec3(ex_worldPos);     // Fragment position
    vec4 texColor = texture(textureSampler, ex_texCoords);  // Sample texture color

    vec4 totalLight = vec4(0.0);  // Initialize total lighting

    // Iterate through all lights and calculate the lighting
    for (int i = 0; i < numberOfLights; i++) {
        totalLight += calculateLight(lights[i], norm, viewDir, fragPos, texColor);
    }

    fragColor = totalLight;  // Output final color after lighting calculation
}
