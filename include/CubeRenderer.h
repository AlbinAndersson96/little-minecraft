#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BasicShader.h"

class CubeRenderer
{
public:
	CubeRenderer();
	~CubeRenderer();

	void render(glm::vec3 pos, glm::vec3 scale, glm::mat4 cameraMatrix, glm::mat4 projectionMatrix);

private:

	unsigned int _VAO;
	unsigned int _VBO;
	unsigned int _EBO;

	BasicShader* _basicShader;
};