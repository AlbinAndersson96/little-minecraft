#include "BasicShader.h"

BasicShader::BasicShader()
{
	const char* vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 worldMatrix;\n"
		"uniform mat4 cameraMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projectionMatrix * cameraMatrix * worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const char* fragmentShaderSource = 
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	_program = glCreateProgram();
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	glLinkProgram(_program);
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

BasicShader::~BasicShader()
{
	glDeleteProgram(_program);
}

void BasicShader::setUniformMat4(const char* name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(_program, name), 1, GL_FALSE, &matrix[0][0]);
}
