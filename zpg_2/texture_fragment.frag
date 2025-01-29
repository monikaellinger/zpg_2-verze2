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
    // Naètení texturové barvy
    vec4 texColor = texture(textureSampler, ex_texCoords);

    // Inicializace svìtelných složek
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * texColor;
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    // Normalizace normály a pohledového smìru
    vec3 norm = normalize(ex_worldNorm);
    vec3 viewDir = normalize(viewPosition - ex_worldPos);

    // Smyèka pøes všechna svìtla
    for (int i = 0; i < numberOfLights; i++) {
        if (lights[i].type == LIGHT_TYPE_POINT) {
            // Výpoèty pro bodové svìtlo
            vec3 lightDir = normalize(lights[i].position - ex_worldPos);
            float distance = length(lights[i].position - ex_worldPos);

            // Attenuation (zeslabení svìtla)
            float attenuation = 1.0 / (lights[i].constant + 
                                       lights[i].linear * distance + 
                                       lights[i].quadratic * (distance * distance));

            // Difuzní složka
            float diff = max(dot(norm, lightDir), 0.0);
            diffuse += vec4(lights[i].color * diff * attenuation, 1.0) * texColor;

            // Spekulární složka
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Shininess = 32
            specular += vec4(lights[i].color * spec * attenuation, 1.0);
        }
          if (lights[i].type == LIGHT_TYPE_SPOT) {
            vec3 camera_direction = normalize(viewPosition - ex_worldPos);
			vec3 light_direction = normalize(lights[i].position - ex_worldPos);
			float attenuation = 1.0;
			float spotlight_intensity = 1.0;

            float theta = dot(light_direction, normalize(-lights[i].direction));
            spotlight_intensity = (theta - lights[i].cutoff) / (1 - lights[i].cutoff);
            if (theta <= lights[i].cutoff) {
				continue;
			}

			vec3 reflection_direction = reflect(-light_direction, ex_worldNorm);

			float light_distance = length(lights[i].position - ex_worldPos);

			attenuation = 1.0 / (lights[i].constant + (lights[i].linear * light_distance) + (lights[i].quadratic * pow(light_distance, 2)));

			float diffuse_strength = max(dot(normalize(light_direction), normalize(ex_worldNorm)), 0.0);
			diffuse += vec4((diffuse_strength * attenuation * spotlight_intensity ) * lights[i].color, 1) * texColor;

			float spec = max(dot(camera_direction, reflection_direction), 0.0);
			spec = pow(spec, 32);
			specular += spec * attenuation * vec4(lights[i].color, 1.0);

        }
    }

    // Výsledná barva fragmentu
    fragColor = (ambient + diffuse + specular) * objectColor;
}
