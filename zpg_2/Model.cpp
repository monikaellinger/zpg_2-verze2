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
	//glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, NULL);
}


Model* Model::createTriangle()
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_points), triangle_points, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glBindVertexArray(0);

	return new Model(GL_TRIANGLES, triangle_points, vao, vbo, 3);
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

Model* Model::createSphere()
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glBindVertexArray(0);

	return new Model(GL_TRIANGLES, sphere, vao, vbo, 2880);
}

Model* Model::createPlain()
{
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW);
	//vertex attribute object(VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

	return new Model(GL_TRIANGLES, plain, VAO, VBO, 6);
}

Model* Model::createSkycube()
{
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), &skycube[0], GL_STATIC_DRAW);

	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glBindVertexArray(0);



	return new Model(GL_TRIANGLES, triangle_points, VAO, VBO, 3);
}



Model* Model::createLogin(const std::string& filePath)
{
	Assimp::Importer importer;
	int import_options = aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace;
	const aiScene* scene = importer.ReadFile(filePath, import_options);

	if (!scene || !scene->mRootNode) {
		std::cerr << "Error loading model: " << filePath << std::endl;
		return nullptr;
	}

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	// Explicitnì definovaný typ pro parametr node a parentTransform
	std::function<void(aiNode*, const aiMatrix4x4&)> processNode = [&](aiNode* node, const aiMatrix4x4& parentTransform) {
		aiMatrix4x4 nodeTransform = parentTransform * node->mTransformation;

		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			// Process all vertices of the mesh
			for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
				Vertex vertex;

				if (mesh->HasPositions()) {
					vertex.Position[0] = mesh->mVertices[j].x;
					vertex.Position[1] = mesh->mVertices[j].y;
					vertex.Position[2] = mesh->mVertices[j].z;
				}

				if (mesh->HasNormals()) {
					vertex.Normal[0] = mesh->mNormals[j].x;
					vertex.Normal[1] = mesh->mNormals[j].y;
					vertex.Normal[2] = mesh->mNormals[j].z;
				}

				if (mesh->HasTextureCoords(0)) {
					vertex.Texture[0] = mesh->mTextureCoords[0][j].x;
					vertex.Texture[1] = mesh->mTextureCoords[0][j].y;
				}

				if (mesh->HasTangentsAndBitangents()) {
					vertex.Tangent[0] = mesh->mTangents[j].x;
					vertex.Tangent[1] = mesh->mTangents[j].y;
					vertex.Tangent[2] = mesh->mTangents[j].z;
				}

				aiVector3D transformedPosition = nodeTransform * mesh->mVertices[j];
				vertex.Position[0] = transformedPosition.x;
				vertex.Position[1] = transformedPosition.y;
				vertex.Position[2] = transformedPosition.z;

				vertices.push_back(vertex);
			}

			// Process indices
			for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
				aiFace& face = mesh->mFaces[j];
				for (unsigned int k = 0; k < face.mNumIndices; k++) {
					indices.push_back(face.mIndices[k]);
				}
			}
		}

		// Recursively process child nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], nodeTransform);
		}
		};

	processNode(scene->mRootNode, aiMatrix4x4());

	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Texture));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));

	glBindVertexArray(0);

	return new Model(GL_TRIANGLES, nullptr, vao, vbo, indices.size());
}

