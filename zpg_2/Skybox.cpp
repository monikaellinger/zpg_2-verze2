#include "Skybox.h"

Skybox::Skybox()
{
	this->followCamera = true;
	this->shaderProgram = new ShaderProgram("TestVertex.glsl", "TestFragment.glsl");
	this->texture = new CubeTexture(1);
	this->modelMatrix = glm::mat4(1.0f);
	this->viewMatrix = glm::mat4(1.0f);
	this->projectionMatrix = glm::mat4(1.0f);
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), &skycube, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Skybox::draw()
{
	this->shaderProgram->use();
	this->shaderProgram->setCamMatrix(this->projectionMatrix, this->viewMatrix);
	this->shaderProgram->setMat4Uniform("modelMatrix", this->modelMatrix);
	glBindVertexArray(this->VAO);
	this->texture->bind();
	this->shaderProgram->setIntUniform("skybox", 1);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glClear(GL_DEPTH_BUFFER_BIT);

	this->texture->unbind();
	glBindVertexArray(0);
	//this->shaderProgram->stop();
	glUseProgram(0);

}

void Skybox::update(Subject* subject)
{
	if (auto camera = dynamic_cast<Camera*>(subject)) {
		this->shaderProgram->setMat4Uniform("viewMatrix", camera->getViewMatrix());
		this->shaderProgram->setMat4Uniform("projectionMatrix", camera->getProjectionMatrix(45.0f, 0.1f, 100.0f));
		this->modelMatrix = glm::translate(glm::mat4(1.0f), camera->getPosition());
	}
}

ShaderProgram* Skybox::getShaderProgram() const
{
	return shaderProgram;
}


