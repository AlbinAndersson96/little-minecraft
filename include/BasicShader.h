#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <iostream>

class BasicShader
{
public:
	BasicShader();
	~BasicShader();

	void setUniformMat4(const char* name, glm::mat4 matrix);

	unsigned int _program;
};