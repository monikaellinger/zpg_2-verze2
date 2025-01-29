#version 330 core

// Vstupy z vertex shaderu
in vec3 ex_worldPos;
in vec3 ex_worldNorm;
in vec2 ex_texCoords;

// V�stup fragment shaderu
out vec4 fragColor;

// Konstanty
#define MAX_LIGHTS 101
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2

// Struktura pro sv�tla
struct Light {
    int type;             // Typ sv�tla: POINT, DIRECTIONAL, nebo SPOT
    vec3 position;        // Pozice sv�tla (u sm�rov�ho se interpretuje jako sm�rov� vektor)
    vec3 color;           // Barva sv�tla
    vec3 direction;       // Sm�r sv�tla (pro sm�rov� a reflektor)
    float cutoff;         // Kosinus vnit�n�ho �hlu pro reflektor
    float outerCutoff;    // Kosinus vn�j��ho �hlu pro reflektor (m�kk� p�echod)
    float constant;
    float linear;
    float quadratic;
};

// Uniformy
uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPosition;
uniform vec4 objectColor;
uniform sampler2D textureSampler; // Texturov� sampler

void main() {
    vec3 test = viewPosition * 2;
    // Na�ten� texturov� barvy
    vec4 texColor = texture(textureSampler, ex_texCoords);

    // V�sledn� barva fragmentu
    fragColor = texColor * objectColor;
}
