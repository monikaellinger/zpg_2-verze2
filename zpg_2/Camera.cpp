#include "Camera.h"

// Konstruktor kamery
Camera::Camera(glm::vec3 startPosition, glm::vec3 upDirection, float startYaw, float startPitch)
    : position(startPosition), worldUp(upDirection), yaw(startYaw), pitch(startPitch),
    speed(5.0f), sensitivity(0.1f)
{
    updateCameraVectors();
}

// P�id�n� pozorovatele (Observer)
void Camera::addObserver(Observer* observer) {
    observers.push_back(observer);
}

// Informov�n� pozorovatel� o zm�n�
void Camera::notifyObservers() {
    for (Observer* observer : observers) {
        observer->update(viewMatrix);
    }
}

// Aktualizace pohledov� matice
void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, position + front, up);
    notifyObservers();  // Informov�n� pozorovatel� o zm�n�
}

// Zpracov�n� kl�vesnice
void Camera::processKeyboard(int direction, float deltaTime) {
    float velocity = speed * deltaTime;
    if (direction == GLFW_KEY_W) position += front * velocity;
    if (direction == GLFW_KEY_S) position -= front * velocity;
    if (direction == GLFW_KEY_A) position -= right * velocity;
    if (direction == GLFW_KEY_D) position += right * velocity;
    updateViewMatrix();
}

// Zpracov�n� pohybu my�i
void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Omez�me rozsah pitch
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
    updateViewMatrix();
}

// Aktualizace sm�rov�ch vektor� kamery (front, right, up)
void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
