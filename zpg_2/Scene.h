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

#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Skybox.h"
#include "Camera.h"

class Scene
{
private:
	vector<DrawableObject*> objects;
	vector<Skybox*> skybox_objects;
	vector<DrawableObject*> triangle_objects;
	ShaderProgram* shader_program;
	bool triangle;
	bool forest;
	bool balls;

public:
	Camera* camera;
	Scene(vector<DrawableObject*>& objects);
	Scene(vector<Skybox*>& skybox_objects);
	Scene(vector<DrawableObject*>& objects, ShaderProgram* shader_program);
	void render(Camera* camera);
	void addObject(DrawableObject* obj);
	ShaderProgram* getShaderProgram();
};

 