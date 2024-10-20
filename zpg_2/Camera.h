#pragma once
//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#include <glm/glm.hpp>
#include <vector>

// Rozhraní Observer
class Observer {
public:
    virtual void update(const glm::mat4& viewMatrix) = 0;  // Funkce, kterou musí implementovat všechny pozorované objekty
};

// Tøída Camera
class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float speed;
    float sensitivity;

    glm::mat4 viewMatrix;
    std::vector<Observer*> observers;

    Camera(glm::vec3 startPosition, glm::vec3 upDirection, float startYaw, float startPitch);

    void addObserver(Observer* observer);
    void notifyObservers();
    void updateViewMatrix();

    void processKeyboard(int direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);

private:
    void updateCameraVectors();
};


