#include "Model.h"

Model::Model(GLenum drawMode, const float* points) {

	this->drawMode = drawMode;
	this->points = points;

	

	//vertex buffer object (VBO)
	glGenBuffers(1, &this->vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, 92814 * 6 * sizeof(float), this->points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &this->vao); 
	glBindVertexArray(this->vao);

	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glBindVertexArray(0);
}


Model* Model::createTree()
{

	return new Model(GL_TRIANGLES, tree);
}


void Model::drawModel()
{
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 92814);
}
