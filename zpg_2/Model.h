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

#include <GL/glew.h>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "triangle.h"
#include "plain.h"
#include "sphere.h"
#include "tree.h"
#include "bushes.h"
#include "cube.h"
#include <string>

using namespace std;

// used for obj only
struct Vertex {
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};

class Model
{
private:
	GLuint vao;
	GLuint vbo;

	const float* points;
	GLenum drawMode;
	int numVertices;
	int draw; // elements/array

public:
	Model(GLenum drawMode, const float* points, GLuint vao, GLuint vbo, int numVertices, int draw);
	void drawModelElements();
	void drawModelArrays();
	static Model* createTriangle();
	static Model* createTree();
	static Model* createBush();
	static Model* createSphere();
	static Model* createPlain();
	static Model* createSkycube();
	static Model* createLogin(const string& filePath);
	int getDraw();
};

