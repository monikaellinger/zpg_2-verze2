#version 330
		out vec4 frag_colour;
		uniform vec4 objectColor;
		void main () {
		     frag_colour = objectColor;
		}