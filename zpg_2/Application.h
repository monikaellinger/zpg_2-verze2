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

#include "Model.h"
#include "Shader.h"
#include "Scene.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Transformation.h"



class Application
{
private:
	
	GLFWwindow* window;
	Shader* vertexShader;
	Shader* fragmentShader;
	ShaderProgram* shaderProgram;
	Model* model;
	static void error_callback(int error, const char* description);
	/*	
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	*/
public:
	
	Application();
	~Application();
	void initialize();
	void compileShaders();
	void run();
};

