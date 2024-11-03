#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 obj_color)
{
	this->position = position;
	this->color = color;
	this->obj_color = obj_color;
}

void Light::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Light::setColor(glm::vec3 color)
{
	this->color = color;
}