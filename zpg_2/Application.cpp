#include "Application.h"


Application::Application()
{

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
	/*
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";
*/
	const char* vertex_shader_def =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"uniform mat4 modelMatrix;"
		"void main () {"
		"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"}";
		
	const char* fragment_shader_tree_def =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.0, 1.0, 0.0, 1.0);" // green
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

	/*
	this->vertex_shader = new Shader(GL_VERTEX_SHADER, vertex_shader_def);
	this->fragment_shader_tree = new Shader(GL_FRAGMENT_SHADER, fragment_shader_tree_def);
	this->fragment_shader_bush = new Shader(GL_FRAGMENT_SHADER, fragment_shader_tree_def);
	
	this->shader_program_tree = new ShaderProgram(vertex_shader, fragment_shader_tree);
	this->shader_program_tree->createShaderProgram();

	this->shader_program_bush = new ShaderProgram(vertex_shader, fragment_shader_bush);
	this->shader_program_bush->createShaderProgram();
	*/
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
	this->bush_obj_1->addModelTransformation(tree_model_2, transform_tree2);
	/*
	Model* bush2 = Model::createBush();
	Transformation* transform_bush2 = new Transformation();
	transform_bush2->scale(0.5f);
	glm::vec3 translation_bush2(2.0f, -5.0f, 0.0f);
	transform_bush2->translate(translation_bush2);
	*/
	
	vector<DrawableObject*> objects = { tree_model_1, tree_model_2, bush_model_1 };
	for (DrawableObject* obj : objects) {
		obj->draw();
	}

	return objects;
}
/*
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {

	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}
*/
void Application::initialize()
{
	glfwSetErrorCallback(this->error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

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

void Application::run()
{
	/*
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);*/

	glEnable(GL_DEPTH_TEST);
	
	

	//GLint idModelTransform = glGetUniformLocation(shader_program_tree->getProgramId(), "modelMatrix");


	while (!glfwWindowShouldClose(this->window))
	{		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
		if (idModelTransform == -1) {
			fprintf(stderr, "Uniform variable 'modelMatrix' not found in shader program.\n");
		}
		*/
		vector<DrawableObject*> forestObjects = createForest();
		Scene scene_forest(forestObjects);

		glfwPollEvents();
		glfwSwapBuffers(this->window);
	}
	
	glfwTerminate();
	exit(EXIT_SUCCESS);

}
