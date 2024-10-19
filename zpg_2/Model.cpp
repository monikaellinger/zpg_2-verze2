#include "Model.h"

Model::Model(GLenum drawMode, const float* points, GLuint vao, GLuint vbo, int numVertices) {

	this->drawMode = drawMode;
	this->points = points;
	this->vao = vao;
	this->vbo = vbo;
	this->numVertices = numVertices;
}

void Model::drawModel()
{
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

Model* Model::createTree()
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0); // Pozice
	glEnableVertexAttribArray(1); // Normály (nebo barvy)

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glBindVertexArray(0); 

	return new Model(GL_TRIANGLES, tree, vao, vbo, 92814);
}

Model* Model::createBush()
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bushes), bushes, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0); // Pozice
	glEnableVertexAttribArray(1); // Normály (nebo barvy)

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glBindVertexArray(0);

	return new Model(GL_TRIANGLES, bushes, vao, vbo, 8730);
}


void Model::drawTree()
{
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, (sizeof(tree) / sizeof(tree[0]))/6);
}

void Model::drawBush()
{
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, (sizeof(bushes) / sizeof(bushes[0])) / 6);
}