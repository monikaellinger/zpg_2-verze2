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
#include "Camera.h"



class Application
{
private:
	
	GLFWwindow* window;

	Shader* vertex_shader;
	Shader* fragment_shader_tree;
	Shader* fragment_shader_bush;
	ShaderProgram* shader_program_tree;
	ShaderProgram* shader_program_bush;

	
	Model* model;
	DrawableObject* tree_obj_1;
	DrawableObject* tree_obj_2;
	DrawableObject* bush_obj_1;
	DrawableObject* bush_obj_2;
	vector<DrawableObject*> objects;
	Scene* sceneForest;
	bool forest;

	Camera* camera;  // Pøidáme ukazatel na kameru
	float lastX, lastY;  // Sledování poslední pozice myši
	bool firstMouse;     // První pohyb myší

	static void error_callback_static(int error, const char* description);
	static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback_static(GLFWwindow* window, int focused);
	static void window_iconify_callback_static(GLFWwindow* window, int iconified);
	static void window_size_callback_static(GLFWwindow* window, int width, int height);
	static void cursor_callback_static(GLFWwindow* window, double x, double y);
	static void button_callback_static(GLFWwindow* window, int button, int action, int mode);

public:
	
	Application();
	~Application();
	void initialize();

	void compileShaders();
	vector<DrawableObject*> createForest();
	void run();

	void error_callback(int error, const char* description);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void window_focus_callback(GLFWwindow* window, int focused);
	void window_iconify_callback(GLFWwindow* window, int iconified);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void cursor_callback(GLFWwindow* window, double x, double y);
	void button_callback(GLFWwindow* window, int button, int action, int mode);
};

