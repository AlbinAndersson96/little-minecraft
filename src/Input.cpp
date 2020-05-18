#include "Input.h"
#include <algorithm>

std::vector<Input*> Input::_instances;

Input::Input(std::vector<int> keysToMonitor, int screenWidth, int screenHeight) 
: _isEnabled(true)
,_pitch(0.0f)
,_yaw(0.0f)
,_firstMouseInput(false)
{
    for (int key : keysToMonitor) 
    {
        _keys[key] = false;
    }

    _lastMouseXPos = screenWidth / 2;
    _lastMouseYPos = screenHeight / 2;

    Input::_instances.push_back(this);
}

Input::~Input() 
{
    _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}

bool Input::isKeyDown(int key) 
{
    bool result = false;

    if (_isEnabled) 
    {
        std::map<int, bool>::iterator it = _keys.find(key);
        if (it != _keys.end()) 
        {
            result = _keys[key];
        }
    }
    return result;
}

void Input::setIsKeyDown(int key, bool isDown) 
{
    std::map<int, bool>::iterator it = _keys.find(key);

    if (it != _keys.end()) 
    {
        _keys[key] = isDown;
    }
}

glm::vec3 Input::getCameraFront()
{
    return _cameraFront;
}

void Input::setupInputs(GLFWwindow* window) 
{
    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetCursorPosCallback(window, Input::mouseCallback);
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    for (Input* keyInput : _instances) 
    {
        keyInput->calculateCameraFront(xpos, ypos);
    }
}

void Input::calculateCameraFront(double xpos, double ypos)
{
    if (_firstMouseInput)
    {
        _lastMouseXPos = xpos;
        _lastMouseYPos = ypos;
        _firstMouseInput = false;
    }
  
    float xoffset = xpos - _lastMouseXPos;
    float yoffset = _lastMouseYPos - ypos; 
    _lastMouseXPos = xpos;
    _lastMouseYPos = ypos;

    float sensitivity = 0.5f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;

    if(_pitch > 89.0f)
        _pitch = 89.0f;
    if(_pitch < -89.0f)
        _pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    direction.y = sin(glm::radians(_pitch));
    direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _cameraFront = glm::normalize(direction);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    for (Input* keyInput : _instances) 
    {
        keyInput->setIsKeyDown(key, action != GLFW_RELEASE);
    }
}