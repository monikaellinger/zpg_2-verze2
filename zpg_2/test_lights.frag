#version 330 core

in vec3 ex_worldPos;
in vec3 ex_worldNorm;

out vec4 fragColor;

#define MAX_LIGHTS 101
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2

struct Light {
    int type;             // Typ sv�tla: POINT, DIRECTIONAL, nebo SPOT
    vec3 position;        // Pozice sv�tla (u sm�rov�ho se interpretuje jako sm�rov� vektor)
    vec3 color;           // Barva sv�tla (v�etn� ambientn� slo�ky)
    vec3 direction;       // Sm�r sv�tla (pro sm�rov� a reflektor)
    float cutoff;         // Kosinus vnit�n�ho �hlu pro reflektor
    float outerCutoff;    // Kosinus vn�j��ho �hlu pro reflektor (m�kk� p�echod)
    float constant;
    float linear;
    float quadratic;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPosition;
uniform vec4 objectColor;

void main() {
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);
    vec4 ambient = objectColor * 0.1; // Z�kladn� ambientn� slo�ka


    for (int i = 0; i < numberOfLights; i++) {
        if (lights[i].type == LIGHT_TYPE_POINT) {
    vec3 lightDir = normalize(lights[i].position - ex_worldPos);
    float distance = length(lights[i].position - ex_worldPos);

    // �tlum
    float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);

    // Dif�zn� slo�ka
    float diff = max(dot(normalize(ex_worldNorm), lightDir), 0.0);
    vec3 diffuseComponent = diff * lights[i].color;

    // Spekul�rn� slo�ka
    vec3 reflectDir = reflect(-lightDir, normalize(ex_worldNorm));
    vec3 viewDir = normalize(viewPosition - ex_worldPos);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specularComponent = spec * lights[i].color;

    // P�id�n� k celkov�mu osv�tlen�
    diffuse += vec4(diffuseComponent * attenuation, 1.0);
    specular += vec4(specularComponent * attenuation, 1.0);
}


        else if (lights[i].type == LIGHT_TYPE_SPOT) {
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
			diffuse += vec4((diffuse_strength * attenuation * spotlight_intensity ) * lights[i].color, 1);

			float spec = max(dot(camera_direction, reflection_direction), 0.0);
			spec = pow(spec, 32);
			specular += spec * attenuation * vec4(lights[i].color, 1.0);
        }
     }
     // Kombinace sv�teln�ch slo�ek
     fragColor = (ambient + diffuse + specular) * objectColor;
}
