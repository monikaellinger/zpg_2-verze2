#pragma once
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Light
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 obj_color;
	Light(glm::vec3 position, glm::vec3 color);
	Light(glm::vec3 position, glm::vec3 color, glm::vec3 obj_color);
	//Light(glm::vec3 obj_color);
	//void setPosition(glm::vec3 position);
};
