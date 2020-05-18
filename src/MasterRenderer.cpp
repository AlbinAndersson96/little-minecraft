#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
{
	_quadRenderer = new QuadRenderer();
	_cubeRenderer = new CubeRenderer();
}

MasterRenderer::~MasterRenderer()
{
	delete(_quadRenderer);
	delete(_cubeRenderer);
}

void MasterRenderer::renderQuad(glm::vec3 pos, glm::vec2 dims, glm::mat4 cameraMatrix, glm::mat4 projectionMatrix)
{
	_quadRenderer->render(pos, dims, cameraMatrix, projectionMatrix);
}

void MasterRenderer::renderCube(glm::vec3 pos, glm::vec3 scale, glm::mat4 cameraMatrix, glm::mat4 projectionMatrix)
{
	_cubeRenderer->render(pos, scale, cameraMatrix, projectionMatrix);
}
