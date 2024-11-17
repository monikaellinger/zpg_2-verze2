#include "Light.h"



Light::Light(glm::vec4 position, glm::vec4 diffuse, glm::vec4 specular, glm::vec4 color)
{
	this->position = position;
	this->diffuse = diffuse;
	this->specular = specular;
	this->color = color;
}

void Light::setPosition(glm::vec4 new_position)
{
	this->position = new_position;
	//notify();
}

glm::vec3 Light::getPosition()
{
	return position;
}

glm::vec3 Light::getColor()
{
	return color;
}


void Light::attach(Observer* observer)
{
	observers.push_back(observer);
}

void Light::detach(Observer* observer)
{
	observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Light::notify()
{
	for (Observer* observer : observers)
	{
		observer->update(this);
	}
}

