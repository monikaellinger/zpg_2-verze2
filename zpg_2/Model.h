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

#include "triangle.h"
#include "sphere.h"
#include "tree.h"
#include "bushes.h"

class Model
{
private:
	GLuint vao;
	GLuint vbo;
	const float* points;
	GLenum drawMode;
	int numVertices;

public:
	Model(GLenum drawMode, const float* points, GLuint vao, GLuint vbo, int numVertices);
	void drawModel();
	static Model* createTriangle();
	static Model* createTree();
	static Model* createBush();
	static Model* createSphere();
};

