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
	//this->modelMatrix = glm::mat4(1.f);
	for (auto transformation : this->transformations) {
		this->modelMatrix *= transformation;
	}
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &this->modelMatrix[0][0]);
}

void Transformation::rotate(float angle, glm::vec3 axis)
{
	//this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), axis);
	transformations.push_back(glm::rotate(glm::mat4(1.f), glm::radians(angle), axis));
}

void Transformation::spin(float angle,float speed, glm::vec3 axis, float deltaTime)
{
	angle += speed * deltaTime;

	if (angle >= 360.0f) angle -= 360.0f;

	//this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), axis);
	transformations.push_back(glm::rotate(glm::mat4(1.f), glm::radians(angle), axis));
}

void Transformation::updateTranslation(int index, glm::vec3 translation)
{
	transformations[index] = glm::translate(glm::mat4(1.f), translation);
}

void Transformation::updateRotation(int index, glm::vec3 axis, float angle)
{
	transformations[index] = glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
}

void Transformation::setMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

glm::mat4 Transformation::getMatrix()
{
	return this->modelMatrix;
}


void Transformation::scale(float scaleFactor)
{
	//this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(scaleFactor));
	transformations.push_back(glm::scale(glm::mat4(1.f), glm::vec3(scaleFactor)));
}

void Transformation::translate(const glm::vec3& translation)
{
	//this->modelMatrix = glm::translate(this->modelMatrix, translation);
	transformations.push_back(glm::translate(glm::mat4(1.f), translation));
}

void Transformation::translate(const glm::vec3& translation, glm::mat4 matrix)
{
	//this->modelMatrix = glm::translate(matrix, translation);
	transformations.push_back(glm::translate(matrix, translation));
}

