#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 initPos, glm::vec3 initFront, float width, float height);
	~Camera();

	void updateMatrix();
	void setPos(glm::vec3 newPos);
	void setFront(glm::vec3 newFront);
	glm::mat4 getCameraMatrix();
	glm::mat4 getProjectionMatrix();

	glm::vec3 _pos, _front, _up;

private:
	glm::mat4 _cameraMatrix;
	glm::mat4 _projectionMatrix;
};