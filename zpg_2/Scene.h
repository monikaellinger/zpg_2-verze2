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

class Scene
{
private:
	vector<DrawableObject*> objects;
	vector<DrawableObject*> triangle_objects;
	bool triangle;
	bool forest;

public:

	Scene(vector<DrawableObject*>& objects);
	void render(Camera* camera);
	

};

 