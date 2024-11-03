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
	#include <memory>
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

		DrawableObject* sphere;
		DrawableObject* plain;
		DrawableObject* ball_obj_1;
		DrawableObject* ball_obj_2;
		DrawableObject* ball_obj_3;
		DrawableObject* ball_obj_4;
		DrawableObject* light_obj;
		
		vector<DrawableObject*> forest_objects;
		vector<DrawableObject*> triangle_objects;
		vector<DrawableObject*> balls_objects;

		ShaderProgram* light_shader;
		glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

		bool forest_scene;
		bool triangle_scene;
		bool balls;
		Scene* balls_scene;

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

		Camera* camera;
		void compileShaders();
		vector<DrawableObject*> createForest();
		vector<DrawableObject*> createTriangleScene();
		vector<DrawableObject*> createBallsScene();
		void run();

		void error_callback(int error, const char* description);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void window_focus_callback(GLFWwindow* window, int focused);
		void window_iconify_callback(GLFWwindow* window, int iconified);
		void window_size_callback(GLFWwindow* window, int width, int height);
		void cursor_callback(GLFWwindow* window, double x, double y);
		void button_callback(GLFWwindow* window, int button, int action, int mode);
	};

