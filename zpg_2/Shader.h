#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

#include "Shader.h"

class Shader
{
private:
	GLuint shaderID;        // ID of the shader
	GLenum shaderType;		// VERTEX/FRAGMENT
	const char* shaderSource;


public:
	Shader(GLenum shaderType, const char* shaderSource);
	GLuint getShaderId();
	void setUniformMatrix4fv(GLuint programID, const char* uniformName, const glm::mat4& matrix);
	
};

