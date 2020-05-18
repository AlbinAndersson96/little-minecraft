#include <GL/glew.h>

#include "QuadRenderer.h"

QuadRenderer::QuadRenderer()
{

	_basicShader = new BasicShader();

	glGenVertexArrays(1, &_VAO);

	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

	float vertices[] = {
	 1.0f,  1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f 
	};
	unsigned int indices[] = { 
		0, 1, 3,
		1, 2, 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

QuadRenderer::~QuadRenderer()
{
	delete(_basicShader);
}

void QuadRenderer::render(glm::vec3 pos, glm::vec2 dims, glm::mat4 cameraMatrix, glm::mat4 projectionMatrix)
{
	glEnable(GL_DEPTH_TEST);
	glUseProgram(_basicShader->_program);
	_basicShader->setUniformMat4("cameraMatrix", cameraMatrix);
	_basicShader->setUniformMat4("projectionMatrix", projectionMatrix);
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME MODE

	glBindVertexArray(0);
}