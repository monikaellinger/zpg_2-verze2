#include "Color.h"

Color::Color(glm::vec4 color)
{
	this->color = color;
}

glm::vec4 Color::getColor()
{
	return this->color;
}
