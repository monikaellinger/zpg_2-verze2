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


//#include "Shader.h"
#include "Camera.h"
#include "Observer.h"
#include "ShaderLoader.h"
#include "Light.h"

	class ShaderProgram : public Observer
	{
	private:
		GLuint shaderProgram;
		GLuint programID;
		vector<Light*> lights;
		int lightCount;
	
		
	public:
		ShaderProgram(const char* vertex, const char* fragment);
		ShaderProgram(const char* vertexPath, const char* fragmentPath, vector<Light*> lights);
		void setMat4Uniform(const char* name, glm::mat4 value);
		void setVec3Uniform(const char* name, glm::vec3 value);
		void setVec4Uniform(const char* name, glm::vec4 value);
		void setIntUniform(const char* name, int value);
		void setFloatUniform(const char* name, float value);
		void use();
		void update(Subject* subject) override;
		GLuint getProjectionMatrixID();
		GLuint getViewMatrixID();
		GLuint getTransformID();
		void setCamMatrix(glm::mat4 projectionMat, glm::mat4 viewMat);
		void sendLight(const std::string& baseName, int index, const Light& light);
		void sendAllLights(Camera* camera);
		void stop();
		void setTextureID(GLuint id);
	};

