#include <GL/glew.h>

#include "CubeRenderer.h"

CubeRenderer::CubeRenderer()
{

	_basicShader = new BasicShader();

	glGenVertexArrays(1, &_VAO);

	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

	float vertices[] = {
	-1.0f,  -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = {  // note that we start from 0!
		1, 2, 3,
        3, 1, 2,
        1, 5, 2,
        2, 5, 6,
        5, 4, 6,
        6, 4, 7,
        4, 0, 7,
        7, 0, 3,
        3, 2, 7,
        7, 2, 6,
        4, 5, 0,
        0, 5, 1
	};

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

CubeRenderer::~CubeRenderer()
{
	delete(_basicShader);
}

void CubeRenderer::render(glm::vec3 pos, glm::vec3 scale, glm::mat4 cameraMatrix, glm::mat4 projectionMatrix)
{
	glEnable(GL_DEPTH_TEST);

	//glm::mat4 worldMatrix = glm::scale(glm::mat4(), scale) * glm::translate(glm::mat4(), pos);
	glm::mat4 worldMatrix = glm::transpose(glm::mat4{ 
										1.0f, 0.0f, 0.0f ,pos.x,
										0.0f, 1.0f, 0.0f, pos.y,
										0.0f, 0.0f, 1.0f, pos.z,
										0.0f, 0.0f, 0.0f, 1.0f
									});

	glUseProgram(_basicShader->_program);
	_basicShader->setUniformMat4("worldMatrix", worldMatrix);
	_basicShader->setUniformMat4("cameraMatrix", cameraMatrix);
	_basicShader->setUniformMat4("projectionMatrix", projectionMatrix);
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME MODE

	glBindVertexArray(0);
}