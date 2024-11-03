#version 330
layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vColor;
out vec3 fragColor;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
void main () {
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vPos, 1.0);
     fragColor = vColor;
}