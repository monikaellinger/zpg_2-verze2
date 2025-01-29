#version 330

in vec2 ex_texCoords;

uniform vec4 objectColor; 
uniform sampler2D textureSampler; // Texturový sampler
uniform int numberOfLights;
uniform vec3 viewPosition;

	out vec4 frag_colour;
	void main () {
	vec3 test = viewPosition;
	//vec4 texColor = texture(textureSampler, ex_texCoords);
	     frag_colour = objectColor;
	};