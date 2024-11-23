#version 400

out vec4 fragColour;
uniform sampler2D textureSampler;
uniform int numberOfLights;

in vec2 uvc;

void main() {
    fragColour = texture(textureSampler, uvc) + vec4(vec3(uvc, 1.0), 1.0);
}