 #include "Transformation.h"

Transformation::Transformation()
{
	this->modelMatrix = glm::mat4(1.0f); // vytvori jednotkovou matici
}

Transformation::Transformation(float scale, glm::vec3 translation, float angle, glm::vec3 axis)
{
	this->modelMatrix = glm::mat4(1.0f);
	this->scale(scale);
	this->translate(translation);
	this->rotate(angle, axis);
}


void Transformation::useTransformation(GLuint matrixID)
{
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &this->modelMatrix[0][0]);
}

void Transformation::rotate(float angle, glm::vec3 axis)
{
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), axis);
}

void Transformation::spin(float angle,float speed, glm::vec3 axis, float deltaTime)
{
	angle += speed * deltaTime;

	if (angle >= 360.0f) angle -= 360.0f;

	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), axis);
}


void Transformation::scale(float scaleFactor)
{
	this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(scaleFactor));
}

void Transformation::translate(const glm::vec3& translation)
{
	this->modelMatrix = glm::translate(this->modelMatrix, translation);
}
