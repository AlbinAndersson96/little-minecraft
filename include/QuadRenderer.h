#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "BasicShader.h"

class QuadRenderer
{
public:
	QuadRenderer();
	~QuadRenderer();

	void render(glm::vec3 pos, glm::vec2 dims, glm::mat4 cameraMatrix, glm::mat4 projectionMatrix);

private:

	unsigned int _VAO;
	unsigned int _VBO;
	unsigned int _EBO;

	BasicShader* _basicShader;
};