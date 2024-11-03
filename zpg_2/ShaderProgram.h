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
#include <vector>
using namespace std;


#include "Shader.h"
#include "Camera.h"
#include "Observer.h"
#include "ShaderLoader.h"

	class ShaderProgram : public Observer
	{
	private:
	
		Shader* vertexShader;
		Shader* fragmentShader;
		GLuint shaderProgram;
		GLuint programID;

	public:
	
		ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
		ShaderProgram(const char* vertex, const char* fragment);
		void use();
		void update(Subject* subject) override;
		GLuint getProjectionMatrixID();
		GLuint getViewMatrixID();
		GLuint getTransformID();
		void setCamMatrix(glm::mat4 projectionMat, glm::mat4 viewMat);
	};

