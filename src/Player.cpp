#include "Player.h"

Player::Player(glm::vec3 pos, glm::vec3 front)
{
	_position = pos;
	_front = front;

	_camera = new Camera(pos, front, 1280.0f, 800.0f);
}

Player::~Player()
{
	delete(_camera);
}

void Player::move(glm::vec3 value)
{
	_position += value * speed;
	_camera->setPos(_camera->_pos + value * speed);
}

void Player::setPosition(glm::vec3 pos)
{
	_position = pos;
	_camera->setPos(_position);
}

void Player::setFront(glm::vec3 front)
{
	_front = front;
	_camera->setFront(front);
}
