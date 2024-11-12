#pragma once


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

#include "ShaderProgram.h"
#include "Observer.h"
#include "Subject.h"


class Camera : public Subject
{
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;


	float yaw;
	float pitch;
	float speed;
	float sensitivity;

	float aspect;

	void updateVectors();

	vector<Observer*> observers;


public:
	Camera(glm::vec3 position, glm::vec3 up);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(float fov, float near, float far);

	void setAspect(float aspect);

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveMouse(float width, float height, float posX, float posY);
	void attach(Observer* observer) override;
	void detach(Observer* observer) override;
	void notify() override;
	glm::vec3 getPosition();
};
