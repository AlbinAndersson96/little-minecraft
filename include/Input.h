#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <map>

class Input
{
public:
	Input(std::vector<int> keys, int screenWidth, int screenHeight);
	~Input();

	bool isKeyDown(int key);
	bool isEnabled() { return _isEnabled; };
	void setIsEnabled(bool value) { _isEnabled = value; };

	glm::vec3 getCameraFront();

	static void setupInputs(GLFWwindow* window);

private:
	void setIsKeyDown(int key, bool isDown);

	std::map<int, bool> _keys;
	bool _isEnabled;

	float _pitch;
	float _yaw;
	float _lastMouseXPos;
	float _lastMouseYPos;
	bool _firstMouseInput;
	glm::vec3 _cameraFront;

	void calculateCameraFront(double xpos, double ypos);

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static std::vector<Input*> _instances;
};