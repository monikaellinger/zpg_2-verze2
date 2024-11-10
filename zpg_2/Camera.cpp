#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up) {
	this->position = position;
	this->worldUp = up;
	this->yaw = -90.f;
	this->pitch = 0.f;
	this->speed = 0.2f;
	this->sensitivity = 0.1f;
	updateVectors();
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

glm::mat4 Camera::getProjectionMatrix(float fov, float aspect, float near, float far) {
	return glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::moveForward() {
	this->position += this->front * this->speed;
	updateVectors();
	notify();
}

void Camera::moveBackward() {
	this->position -= this->front * this->speed;
	updateVectors();
	notify();
}

void Camera::moveLeft() {
	this->position -= this->right * this->speed;
	updateVectors();
	notify();
}

void Camera::moveRight() {
	this->position += this->right * this->speed;
	updateVectors();
	notify();
}

void Camera::moveMouse(float width, float height, float posX, float posY) {
	this->yaw = yaw + (posX - (width / 2)) * sensitivity;
	this->pitch = pitch + ((height / 2) - posY) * sensitivity;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	updateVectors();
	notify();
}

void Camera::attach(Observer* observer)
{
	observers.push_back(observer);
}

void Camera::detach(Observer* observer)
{
	observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notify()
{
	for (Observer* observer : observers)
	{
		observer->update(this);
	}
}

glm::vec3 Camera::getPosition()
{
	return position;
}

void Camera::updateVectors() {
	glm::vec3 newFfront;
	newFfront.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	newFfront.y = sin(glm::radians(this->pitch));
	newFfront.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(newFfront);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}