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
	//#include "Shader.h"
	#include "Scene.h"
	#include "ShaderProgram.h"
	#include "DrawableObject.h"
	#include "Transformation.h"
	#include "Light.h"
	#include "Camera.h"
	#include <chrono>


	class Application
	{
	private:
	
		GLFWwindow* window;

		bool forest_scene;
		bool triangle_scene;
		bool balls_scene;
		bool shaders_example_scene;

		float lastX, lastY; 
		bool firstMouse;    
		glm::mat4 projection;

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
		float getDeltaTime();
		Camera* camera;
		vector<Light*> createLights();
		vector<Light*> createLightsForest();
		vector<DrawableObject*> createForest();
		vector<DrawableObject*> createTriangleScene();
		vector<DrawableObject*> createBallsScene();
		vector<DrawableObject*> createShadersExampleScene();
		void run();

		void error_callback(int error, const char* description);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void window_focus_callback(GLFWwindow* window, int focused);
		void window_iconify_callback(GLFWwindow* window, int iconified);
		void window_size_callback(GLFWwindow* window, int width, int height);
		void cursor_callback(GLFWwindow* window, double x, double y);
		void button_callback(GLFWwindow* window, int button, int action, int mode);
	};

