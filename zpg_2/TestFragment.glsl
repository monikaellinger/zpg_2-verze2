#version 450


in vec3 fragmentLocalPosition;


uniform samplerCube skybox;


out vec4 frag_colour;



void main () {
	 
    frag_colour = texture(skybox, fragmentLocalPosition);
}
