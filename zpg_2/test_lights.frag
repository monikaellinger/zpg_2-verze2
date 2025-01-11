#version 330 core

// Fragment Shader
in vec3 ex_worldPos;
in vec3 ex_worldNorm;

out vec4 fragColor;

#define MAX_LIGHTS 101
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2

struct Light {
    int type;             // Typ svetla: POINT, DIRECTIONAL, nebo SPOT
    vec3 position;        // Pozice svetla (u smeroveho se interpretuje jako smerovy vektor)
    vec3 color;           // Barva svetla (vcetne ambientni slozky)
    vec3 direction;       // Smer svetla (pro smerove a reflektor)
    float cutoff;         // Kosinus vnitrniho uhlu pro reflektor
    float outerCutoff;    // Kosinus vnejsiho uhlu pro reflektor (mekky prechod)
    float constant;
    float linear;
    float quadratic;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPosition;
uniform vec4 objectColor;

void main() {
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    

    for (int i = 0; i < numberOfLights; i++) {
        if (lights[i].type == LIGHT_TYPE_POINT) {
            /*vec3 view_direction = normalize(viewPosition - ex_worldPos);
            vec3 light_direction  = normalize(lights[i].position - ex_worldPos);
            float light_distance = length(lights[i].position - ex_worldPos);

            float attenuation = 1.0 / (lights[i].constant + (lights[i].linear * light_distance) + (lights[i].quadratic * pow(light_distance, 2)));
   
            ambient += vec4(lights[i].color * 0.1, 1.0);

            float diff = max(dot(ex_worldNorm, light_direction), 0.0);
            diffuse += vec4((diff * lights[i].color) * attenuation, 1.0);;

            vec3 halfwayDir = normalize(light_direction + view_direction);
            float spec = pow(max(dot(ex_worldNorm, halfwayDir), 0.0), 32.0);
            specular += vec4((spec * lights[i].color) * attenuation, 1.0);
            */

            vec3 camera_direction = normalize(viewPosition - ex_worldPos);
            vec3 light_direction = normalize(lights[i].position - ex_worldPos);
            float attenuation = 1;
            vec3 reflection_direction = reflect(-light_direction, ex_worldNorm);

            float light_distance = length(lights[i].position - ex_worldPos);

            attenuation = 1.0 / (lights[i].constant + (lights[i].linear * light_distance) + (lights[i].quadratic * pow(light_distance, 2)));

            float diffuse_strength = max(dot(normalize(light_direction), normalize(ex_worldNorm)), 0.0);
            diffuse += vec4((diffuse_strength * 1.0 * attenuation ) * lights[i].color, 1);

            float spec = max(dot(camera_direction, reflection_direction), 0.0);
            spec = pow(spec, 32);  
            specular += spec * 1.0 * attenuation * vec4(lights[i].color, 1.0);
        }
    }

    fragColor = (ambient + diffuse + specular) * objectColor;
}
