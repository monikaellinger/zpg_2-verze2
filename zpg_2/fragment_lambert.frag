// LAMBERT
#version 330

in vec4 ex_worldPos;
in vec3 ex_worldNorm;

out vec4 fragColor;

uniform vec4 objectColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;

void main() {
    vec3 lightDir = normalize(lightPosition - vec3(ex_worldPos));
    vec3 norm = normalize(ex_worldNorm);

    // Dif�zn� slo�ka, z�kladn� Lambert�v model
    float diff = max(dot(norm, lightDir), 0.0);

    // Ambientn� slo�ka
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    // V�po�et dif�zn� slo�ky sv�tla
    vec4 diffuse = diff * vec4(objectColor) * vec4(lightColor, 1.0);

    // Kone�n� barva fragmentu jako sou�et ambientn� a dif�zn� slo�ky
    fragColor = ambient + diffuse;
}
