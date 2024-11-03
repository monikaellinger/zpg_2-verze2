#version 330

in vec4 ex_worldPos;
in vec3 ex_worldNorm;

out vec4 fragColor;

uniform vec3 viewPosition;

void main() {
    vec3 objectColor = vec3(0.1, 0.1, 0.1);
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    vec3 lightDir = normalize(lightPosition - vec3(ex_worldPos));
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos));
    vec3 norm = normalize(ex_worldNorm);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(lightDir, normalize(ex_worldNorm)), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 diffuse = diff * vec4(objectColor, 1.0) * vec4(lightColor, 1.0);
    vec4 specular = spec * vec4(lightColor, 1.0);
    
    fragColor = ambient + diffuse + specular;
}