#version 330

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoords; // Texturové souøadnice

out vec4 ex_worldPos;
out vec3 ex_worldNorm;
out vec2 ex_texCoords; // Výstupní texturové souøadnice

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPos, 1.0);
    ex_worldPos = modelMatrix * vec4(vPos, 1.0);
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    ex_worldNorm = normalMatrix * vNormal;
    ex_texCoords = vTexCoords; // Pøedání do fragment shaderu
}
