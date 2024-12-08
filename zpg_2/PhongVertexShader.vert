#version 450

layout(location = 0) in vec3 vp;  // Position
layout(location = 1) in vec3 vn;  // Normal
layout(location = 2) in vec2 vt;  // Texture Coordinates
layout(location = 3) in vec3 ts;  // Tangent Space

uniform mat4 modelMatrix;  // Model transformation matrix
uniform mat4 viewMatrix;   // View (camera) transformation matrix
uniform mat4 projectionMatrix;  // Projection transformation matrix

out vec2 uv;  // Texture coordinates to pass to the fragment shader
out vec4 ex_worldPos;  // World position of the vertex
out vec3 ex_worldNorm;  // World-normal of the vertex

void main() {
    uv = vt;  // Pass texture coordinates to fragment shader
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);  // Final position
    ex_worldPos = modelMatrix * vec4(vp, 1.0);  // World position
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));  // Normal matrix
    ex_worldNorm = normalMatrix * vn;  // Transformed normal
}
