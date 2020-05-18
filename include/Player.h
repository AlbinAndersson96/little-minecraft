#pragma once

#include <glm/vec3.hpp>

#include "Camera.h"

class Player
{
public:
	Player(glm::vec3 pos, glm::vec3 front);
	~Player();

	void move(glm::vec3 direction);
	void setPosition(glm::vec3 pos);
	void setFront(glm::vec3 front);

	Camera* _camera;
	glm::vec3 _position, _front;

	float speed = 0.1f;
};