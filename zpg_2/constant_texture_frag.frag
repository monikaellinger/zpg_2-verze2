#version 330 core

// Vstupy z vertex shaderu
in vec3 ex_worldPos;
in vec3 ex_worldNorm;
in vec2 ex_texCoords;

// Výstup fragment shaderu
out vec4 fragColor;

// Konstanty
#define MAX_LIGHTS 101
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2

// Struktura pro svìtla
struct Light {
    int type;             // Typ svìtla: POINT, DIRECTIONAL, nebo SPOT
    vec3 position;        // Pozice svìtla (u smìrového se interpretuje jako smìrový vektor)
    vec3 color;           // Barva svìtla
    vec3 direction;       // Smìr svìtla (pro smìrové a reflektor)
    float cutoff;         // Kosinus vnitøního úhlu pro reflektor
    float outerCutoff;    // Kosinus vnìjšího úhlu pro reflektor (mìkký pøechod)
    float constant;
    float linear;
    float quadratic;
};

// Uniformy
uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPosition;
uniform vec4 objectColor;
uniform sampler2D textureSampler; // Texturový sampler

void main() {
    vec3 test = viewPosition * 2;
    // Naètení texturové barvy
    vec4 texColor = texture(textureSampler, ex_texCoords);

    // Výsledná barva fragmentu
    fragColor = texColor * objectColor;
}
