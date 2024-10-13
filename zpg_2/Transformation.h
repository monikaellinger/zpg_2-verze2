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


class Transformation
{
private:
	glm::mat4 modelMatrix;

public:
	Transformation();
	void scale(float scaleFactor);
	glm::mat4 getMatrix() const;
	/*
	static glm::mat4 createIdentityMatrix();
	static glm::mat4 rotateY(float angle);
	static glm::mat4 rotateX(float angle, const glm::mat4& modelMatrix);
	static glm::mat4 translate(float myView);
	static glm::mat4 combineTransformations(float angleY, float angleX, float myView, float scaleFactor);
	*/
};


