#include "Camera.h"

Camera::Camera(glm::vec3 initPos, glm::vec3 initFront, float width, float height)
: _pos(initPos)
,_front(initFront)
{
	glm::vec3 cameraDirection = glm::normalize(_pos - _front);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	_cameraMatrix = glm::lookAt(_pos, _pos + _front, cameraUp);
	_projectionMatrix = glm::perspective(70.0f, width / height, 0.1f, 150.0f);
}

Camera::~Camera(){}

void Camera::updateMatrix()
{
	glm::vec3 cameraDirection = glm::normalize(_pos - _front);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	_up = cameraUp;

	_cameraMatrix = glm::lookAt(_pos, _pos + _front, cameraUp);
}

void Camera::setPos(glm::vec3 pos)
{
	_pos = pos;
	updateMatrix();
}

void Camera::setFront(glm::vec3 front)
{
	_front = front;
	updateMatrix();
}

glm::mat4 Camera::getCameraMatrix()
{
	return _cameraMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return _projectionMatrix;
}


