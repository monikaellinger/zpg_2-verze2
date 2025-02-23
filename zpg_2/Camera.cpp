#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up) {
	this->position = position;
	this->worldUp = up;
	this->yaw = -90.f;
	this->pitch = 0.f;
	this->speed = 0.2f;
	this->sensitivity = 0.1f;
	this->aspect = 4.f / 3.f;
	updateVectors();
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

glm::mat4 Camera::getProjectionMatrix(float fov, float near, float far) {
	return glm::perspective(glm::radians(fov), this->aspect, near, far);
}


void Camera::setAspect(float aspect)
{
	this->aspect = aspect;
}

void Camera::moveForward() {
	this->position += this->front * this->speed;
	//updateVectors(); - podje J
	notify();
}

void Camera::moveBackward() {
	this->position -= this->front * this->speed;
	//updateVectors(); - podle J
	notify();
}

void Camera::moveLeft() {
	this->position -= this->right * this->speed;
	//updateVectors(); - podle J
	notify();
}

void Camera::moveRight() {
	this->position += this->right * this->speed;
	//updateVectors(); - podle J
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
	//notify(); - podle J
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
	return this->position;
}

glm::vec3 Camera::getFront()
{
	return this->front;
}

void Camera::updateVectors() {
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	newFront.y = sin(glm::radians(this->pitch));
	newFront.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(newFront);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
	this->notify();
}