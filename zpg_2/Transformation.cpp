 #include "Transformation.h"

Transformation::Transformation()
{
	this->modelMatrix = glm::mat4(1.0f); // vytvori jednotkovou matici
}


void Transformation::useTransformation(GLuint matrixID)
{
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &this->modelMatrix[0][0]);
}

void Transformation::rotate(float angle, glm::vec3 axis)
{
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
/*

glm::mat4 Transformation::createIdentityMatrix()
{
	return glm::mat4(1.0f);
}

glm::mat4 Transformation::rotateY(float angle)
{
	return glm::rotate(createIdentityMatrix(), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Transformation::rotateX(float angle, const glm::mat4& modelMatrix)
{
	return glm::rotate(modelMatrix, angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::mat4 Transformation::translate(float myView)
{
	return glm::translate(createIdentityMatrix(), glm::vec3(0.0f, 0.0f, myView));
}



glm::mat4 Transformation::combineTransformations(float angleY, float angleX, float myView, float scaleFactor)
{
	glm::mat4 modelMatrix = createIdentityMatrix();
	modelMatrix = rotateY(angleY);
	modelMatrix = rotateX(angleX, modelMatrix);
	modelMatrix = translate(myView);
	modelMatrix = scale(scaleFactor);
	return modelMatrix;
}
*/