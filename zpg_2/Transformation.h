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
	vector<glm::mat4> transformations;

public:
	Transformation();
	Transformation(float scale, glm::vec3 translation, float angle, glm::vec3 axis);
	void scale(float scaleFactor);
	void translate(const glm::vec3& translation);
	void translate(const glm::vec3& translation, glm::mat4 matrix);
	void useTransformation(GLuint matrixID);
	void rotate(float angle, glm::vec3 axis);
	void spin(float angle, float speed, glm::vec3 axis, float deltaTime);
	void updateTranslation(int index, glm::vec3 translation);
	void updateRotation(int index, glm::vec3 axis, float angle);
	void setMatrix(glm::mat4 modelMatrix);
	glm::mat4 getMatrix();
};


