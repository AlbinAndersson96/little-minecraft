#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <iostream>

#include "MasterRenderer.h"
#include "Input.h"
#include "Player.h"

class Application
{
public:
	Application(int screenWidth, int screenHeight, const char* title);
	~Application();
	
	void run();

private:
	GLFWwindow* _window;
	MasterRenderer* _masterRenderer;

	Input* _inputHandler;
	Player* _player;
};