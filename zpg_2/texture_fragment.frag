#version 330

in vec3 ex_worldPos;
in vec3 ex_worldNorm;
in vec2 ex_texCoords; // P�ijato z vertex shaderu

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
uniform sampler2D textureSampler; // Texturov� sampler


void main() {
    vec4 texColor = texture(textureSampler, ex_texCoords);

    vec4 ambient = objectColor * texColor * 0.1;
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);
    vec3 norm = normalize(ex_worldNorm);
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPos));

    for (int i = 0; i < numberOfLights; i++) {

    if (lights[i].type == LIGHT_TYPE_POINT) {
     vec3 lightDir = normalize(lights[i].position - ex_worldPos);
     float distance = length(lights[i].position - ex_worldPos);

      // �tlum
      float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);


        if (dot(norm, lightDir) > 0.0) {
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

            diffuse = diff * texColor * vec4(lights[i].color, 1.0) * objectColor * attenuation;
            specular = spec * vec4(lights[i].color, 1.0) * attenuation;
        }
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
			diffuse += texColor * vec4((diffuse_strength * attenuation * spotlight_intensity ) * lights[i].color, 1);
			float spec = max(dot(camera_direction, reflection_direction), 0.0);
			spec = pow(spec, 32);
			specular += spec * attenuation * vec4(lights[i].color, 1.0);
    }
    }
    fragColor = (ambient + diffuse + specular) * objectColor;;
}
