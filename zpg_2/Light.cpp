#include "Light.h"


Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutoff, float outerCutoff, float constant, float linear, float quadratic, Camera* camera)
{
	this->position = position;
	this->color = color;
	this->direction = direction;
	this->cutoff = cutoff;
	this->outerCutoff = outerCutoff;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->camera = camera;
}

void Light::setPosition(glm::vec4 new_position)
{
	this->position = new_position;
	notify();
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
	this->position = camera->getPosition();
	this->direction = camera->getFront();
	for (Observer* observer : observers)
	{
		observer->update(this);
	}
}

