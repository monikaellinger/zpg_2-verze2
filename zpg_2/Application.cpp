#include "Application.h"


Application::Application() : lastX(400), lastY(300), firstMouse(true) {
	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	this->forest = true;
}


Application::~Application()
{

}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


void Application::compileShaders()
{
	const char* vertex_shader_def =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vColor;"
		"out vec3 fragColor;"
		"uniform mat4 modelMatrix;"
		"void main () {"
		"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"     fragColor = vColor;"
		"}";
		
	const char* fragment_shader_tree_def =
		"#version 330\n"
		"in vec3 fragColor;"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (fragColor, 1.0);" // green
		"}";

	this->tree_obj_1 = new DrawableObject(new ShaderProgram(new Shader(GL_VERTEX_SHADER, vertex_shader_def), new Shader(GL_FRAGMENT_SHADER, fragment_shader_tree_def)));
	this->tree_obj_2 = new DrawableObject(new ShaderProgram(new Shader(GL_VERTEX_SHADER, vertex_shader_def), new Shader(GL_FRAGMENT_SHADER, fragment_shader_tree_def)));

	const char* fragment_shader_bush_def =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);"
		"}";

	this->bush_obj_1 = new DrawableObject(new ShaderProgram(new Shader(GL_VERTEX_SHADER, vertex_shader_def), new Shader(GL_FRAGMENT_SHADER, fragment_shader_bush_def)));
}

vector<DrawableObject*> Application::createForest()
{
	Model* tree_model_1 = Model::createTree();
	Transformation* transform_tree1 = new Transformation();
	transform_tree1->scale(0.1f);
	glm::vec3 translation_tree1(0.0f, -4.0f, 0.0f);
	transform_tree1->translate(translation_tree1);
	this->tree_obj_1->addModelTransformation(tree_model_1, transform_tree1);


	Model* tree_model_2 = Model::createTree();
	Transformation* transform_tree2 = new Transformation();
	transform_tree2->scale(0.2f);
	glm::vec3 translation_tree2(-2.0f, -5.0f, 0.0f);
	transform_tree2->translate(translation_tree2);
	this->tree_obj_2->addModelTransformation(tree_model_2, transform_tree2);

	Model* bush_model_1 = Model::createBush();
	Transformation* transform_bush1 = new Transformation();
	transform_bush1->scale(0.1f);
	glm::vec3 translation_bush1(1.0f, -4.0f, 0.0f);
	transform_bush1->translate(translation_bush1);
	this->bush_obj_1->addModelTransformation(tree_model_2, transform_bush1);
	
	
	this->objects = { tree_obj_1, tree_obj_2, bush_obj_1 };


	return this->objects;
}

void Application::initialize()
{
	glfwSetErrorCallback(this->error_callback_static);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowUserPointer(this->window, this);
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}


void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == 32 && action == 1) {
		this->forest = !this->forest;
	}

	if (key == 262) {
		this->sceneForest->getObjects()[0]->setRotation(90, glm::vec3(0, 1, 0));
	}
	*/
	

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	float cameraSpeed = 0.05f;  // Mùžete upravit rychlost kamery

	if (key == GLFW_KEY_W) camera->processKeyboard(GLFW_KEY_W, cameraSpeed);
	if (key == GLFW_KEY_S) camera->processKeyboard(GLFW_KEY_S, cameraSpeed);
	if (key == GLFW_KEY_A) camera->processKeyboard(GLFW_KEY_A, cameraSpeed);
	if (key == GLFW_KEY_D) camera->processKeyboard(GLFW_KEY_D, cameraSpeed);

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) { 
	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y;  // Obrácenì, protože y- souøadnice jde smìrem nahoru

	lastX = x;
	lastY = y;

	camera->processMouseMovement(xoffset, yoffset);
	printf("cursor_callback \n"); 
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {

	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void Application::error_callback_static(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->key_callback(window, key, scancode, action, mods);
}

void Application::window_focus_callback_static(GLFWwindow* window, int focused) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->window_focus_callback(window, focused);
}

void Application::window_iconify_callback_static(GLFWwindow* window, int iconified) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->window_iconify_callback(window, iconified);
}

void Application::window_size_callback_static(GLFWwindow* window, int width, int height) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->window_size_callback(window, width, height);
}

void Application::cursor_callback_static(GLFWwindow* window, double x, double y) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->cursor_callback(window, x, y);
}

void Application::button_callback_static(GLFWwindow* window, int button, int action, int mode) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	app->button_callback(window, button, action, mode);
}


void Application::run()
{
	
	glfwSetKeyCallback(window, key_callback_static);
	glfwSetWindowFocusCallback(window, window_focus_callback_static);
	glfwSetWindowIconifyCallback(window, window_iconify_callback_static);
	glfwSetWindowSizeCallback(window, window_size_callback_static);
	glfwSetCursorPosCallback(window, cursor_callback_static);
	glfwSetMouseButtonCallback(window, button_callback_static);

	glEnable(GL_DEPTH_TEST);
	vector<DrawableObject*> forest_objects = createForest();
	Scene scene_forest(forest_objects);
	glm::mat4 viewMatrix = camera->viewMatrix;

	// Promìnné pro deltaTime
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;

	while (!glfwWindowShouldClose(this->window))
	{		
		// Vypoèítání deltaTime
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		;

		if (forest == true) {
			scene_forest.render();
			glfwPollEvents();
			glfwSwapBuffers(this->window);
		}
		
	}
	
	glfwTerminate();
	exit(EXIT_SUCCESS);

}
