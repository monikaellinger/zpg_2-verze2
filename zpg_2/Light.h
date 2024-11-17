#pragma once
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <vector>

#include "Subject.h"
#include "Observer.h"
using namespace std;

class Light : public Subject
{

public:
	vector<Observer*> observers;

	glm::vec4 position;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 color;

	Light(glm::vec4 position, glm::vec4 diffuse, glm::vec4 specular, glm::vec4 color);
	void setPosition(glm::vec4 new_position);
	glm::vec3 getPosition();
	glm::vec3 getColor(); 

	void attach(Observer* observer) override;
	void detach(Observer* observer) override;
	void notify() override;
};

