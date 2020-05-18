#include "Application.h"

Application::Application(int screenWidth, int screenHeight, const char* title)
{
    //INITIALIZE LIBRARIES AND CREATE WINDOW/CONTEXT, GLFW3, GLEW
    if (!glfwInit())
        exit(-1);
    _window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
    if (!_window)
        exit(-1);
    glfwMakeContextCurrent(_window);
    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(-1);

    //SET UP RENDERER
    _masterRenderer = new MasterRenderer();

    glm::vec3 playerInitialPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 playerInitialRotation = glm::vec3(0.0f, 0.0f, -1.0f);

    //SET UP INPUT HANDLER
    _inputHandler = new Input(
                                std::vector<int>{                //KEYS TO MONITOR
                                                GLFW_KEY_W       //MOVE FORWARD
                                                ,GLFW_KEY_S      //MOVE BACKWARD
                                                ,GLFW_KEY_A      //MOVE LEFT
                                                ,GLFW_KEY_D      //MOVE RIGHT
                                                ,GLFW_KEY_C      //MOVE DOWN
                                                ,GLFW_KEY_SPACE  //MOVE UP
                                                ,GLFW_KEY_ESCAPE //EXIT GAME
                                            },
                                screenWidth, screenWidth);
    _inputHandler->setupInputs(_window);

    //SET UP PLAYER
    _player = new Player(playerInitialPosition, playerInitialRotation);
}

Application::~Application()
{
    //CLEANUP
    delete(_masterRenderer);
    delete(_inputHandler);
    delete(_player);

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Application::run()
{
    //MAIN GAME LOOP
    while (!glfwWindowShouldClose(_window))
    {
        //CLEAR BUFFERS
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //CHECK FOR INPUT AND MAKE CORRESPONDING ACTION
        if (_inputHandler->isKeyDown(GLFW_KEY_W))
            _player->move(_player->_front);
        if (_inputHandler->isKeyDown(GLFW_KEY_S))
            _player->move(-_player->_front);
        if(_inputHandler->isKeyDown(GLFW_KEY_A))
            _player->move(-glm::normalize(glm::cross(_player->_front, _player->_camera->_up)));
        if(_inputHandler->isKeyDown(GLFW_KEY_D))
            _player->move(glm::normalize(glm::cross(_player->_front, _player->_camera->_up)));
        if(_inputHandler->isKeyDown(GLFW_KEY_C))
            _player->move(glm::vec3(0.0f, -1.0f, 0.0f));
        if(_inputHandler->isKeyDown(GLFW_KEY_SPACE))
            _player->move(glm::vec3(0.0f, 1.0f, 0.0f));
        if(_inputHandler->isKeyDown(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(_window, 1);

        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
        _player->setFront(_inputHandler->getCameraFront());

        //RENDER A 10x10x10 BLOCK OF CUBES
        for(int x = 0; x<10; ++x)
            for(int y = 0; y<10; ++y)
                for(int z = 0; z<10; ++z)
                    _masterRenderer->renderCube(glm::vec3{2.0f*x, 2.0f*y, 2.0f*z}, glm::vec3{1.0f, 1.0f, 1.0f}, _player->_camera->getCameraMatrix(), _player->_camera->getProjectionMatrix());

        //SWAP BUFFERS AND POLL WINDOW FOR EVENTS
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}