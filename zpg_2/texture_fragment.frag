#version 330

in vec4 ex_worldPos;
in vec3 ex_worldNorm;
in vec2 ex_texCoords; // Pøijato z vertex shaderu

out vec4 fragColor;

#define MAX_LIGHTS 101
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2

struct Light {
    int type;             // Typ svìtla: POINT, DIRECTIONAL, nebo SPOT
    vec4 position;        // Pozice svìtla (u smìrového se interpretuje jako smìrový vektor)
    vec4 diffuse;         // Barva svìtla
    vec4 specular;        // Speculární barva
    vec4 color;           // Barva svìtla (ambientní složka)
    vec3 direction;       // Smìr svìtla (pro smìrové a reflektor)
    float cutoff;         // Kosinus úhlu pro reflektor
    float outerCutoff;    // Kosinus vnìjšího úhlu pro reflektor (mìkký pøechod)
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec3 viewPosition;
uniform vec4 objectColor;
uniform sampler2D textureSampler; // Texturový sampler


vec4 calculateLight(Light light, vec3 norm, vec3 viewDir, vec3 fragPos, vec4 texColor) {
    vec4 ambient = light.color * texColor * 0.1;
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    if (light.type == LIGHT_TYPE_POINT) {
        vec3 lightDir = normalize(vec3(light.position) - fragPos);
        if (dot(norm, lightDir) > 0.0) {
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

            diffuse = diff * light.diffuse * texColor * light.color * objectColor;
            specular = spec * light.specular * light.color;
        }

    } else if (light.type == LIGHT_TYPE_DIRECTIONAL) {
        vec3 lightDir = normalize(vec3(light.position)); // Smìr svìtla
        if (dot(norm, lightDir) > 0.0) {
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

            diffuse = diff * light.diffuse * texColor * light.color * objectColor;
            specular = spec * light.specular * light.color;
        }

    } else if (light.type == LIGHT_TYPE_SPOT) {
        vec3 lightDir = normalize(vec3(light.position) - fragPos);
        float theta = dot(lightDir, normalize(light.direction));
        float epsilon = light.cutoff - light.outerCutoff;
        float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

        if (theta > light.outerCutoff && dot(norm, lightDir) > 0.0) {
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

            diffuse = diff * light.diffuse * texColor * light.color * objectColor * intensity;
            specular = spec * light.specular * light.color * intensity;
        }
    }

    return ambient + diffuse + specular + objectColor;
}

void main() {
    vec3 norm = normalize(ex_worldNorm);
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos));
    vec3 fragPos = vec3(ex_worldPos);
    vec4 texColor = texture(textureSampler, ex_texCoords); // Naètení barvy textury

    vec4 totalLight = vec4(0.0);    

    for (int i = 0; i < numberOfLights; i++) {
        totalLight += calculateLight(lights[i], norm, viewDir, fragPos, texColor);
    }
    fragColor = totalLight;
}
