#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"

class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();

	void renderQuad(glm::vec3 pos, glm::vec2 dims, glm::mat4 cameraMatrix, glm::mat4 projectionMatrix);
	void renderCube(glm::vec3 pos, glm::vec3 scale, glm::mat4 cameraMatrix, glm::mat4 projectionMatrix);

private:
	QuadRenderer* _quadRenderer;
	CubeRenderer* _cubeRenderer;
};