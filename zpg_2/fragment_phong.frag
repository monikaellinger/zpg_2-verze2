#version 330

in vec4 ex_worldPos;
in vec3 ex_worldNorm;

out vec4 fragColor;

#define MAX_LIGHTS 101
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2

struct Light {
    int type;             // Typ sv�tla: POINT, DIRECTIONAL, nebo SPOT
    vec4 position;        // Pozice sv�tla (u sm�rov�ho se interpretuje jako sm�rov� vektor)
    vec4 ambient;         // Ambientn� slo�ka sv�tla
    vec4 diffuse;         // Barva sv�tla
    vec4 specular;        // Specul�rn� barva
    vec4 color;           // Barva sv�tla (ambientn� slo�ka)
    vec3 direction;       // Sm�r sv�tla (pro sm�rov� a reflektor)
    float cutoff;         // Kosinus �hlu pro reflektor
    float outerCutoff;    // Kosinus vn�j��ho �hlu pro reflektor (m�kk� p�echod)
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPosition;
uniform vec4 objectColor;

vec4 calculateLight(Light light, vec3 norm, vec3 viewDir, vec3 fragPos) {
    vec4 ambient = light.ambient * objectColor; // P�id�n� ambientn� slo�ky
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    if (light.type == LIGHT_TYPE_POINT) {
        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;

        vec3 lightDir = normalize(vec3(light.position) - fragPos);
        float distance = length(vec3(light.position) - fragPos);

        // Attenuation calculation
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        if (dot(norm, lightDir) > 0.0) {
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

            // Apply attenuation
            diffuse = diff * light.diffuse * light.color * objectColor * attenuation;
            specular = spec * light.specular * light.color * attenuation;
        }
    } else if (light.type == LIGHT_TYPE_DIRECTIONAL) {
        vec3 lightDir = normalize(-light.direction); // Sm�r sv�tla u directional light
        if (dot(norm, lightDir) > 0.0) { // Kontrola, zda norm�la sm��uje ke sv�tlu
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

            diffuse = diff * light.diffuse * light.color * objectColor;
            specular = spec * light.specular * light.color;
        }
    } else if (light.type == LIGHT_TYPE_SPOT) {
        vec3 lightDir = normalize(vec3(light.position) - fragPos);
        float theta = dot(lightDir, normalize(light.direction));
        float epsilon = light.cutoff - light.outerCutoff;
        float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

        if (theta > light.outerCutoff && dot(norm, lightDir) > 0.0) { // Kontrola norm�ly a ku�ele reflektoru
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

            diffuse = diff * light.diffuse * light.color * objectColor * intensity;
            specular = spec * light.specular * light.color * intensity;
        }
    }

    return ambient + diffuse + specular;
}

void main() {
    vec3 norm = normalize(ex_worldNorm);
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos));
    vec3 fragPos = vec3(ex_worldPos);

    vec4 totalLight = vec4(0.0);

    for (int i = 0; i < numberOfLights; i++) {
        totalLight += calculateLight(lights[i], norm, viewDir, fragPos);
    }
    fragColor = totalLight;
}
