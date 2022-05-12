#include <iostream>
#include "shader.h"

Shader::Shader(const GLchar* vSourcePath, const GLchar* fSourcePath) {
	const char* vShaderSource = ReadShader(vSourcePath);
	const char* fShaderSource = ReadShader(fSourcePath);
	

	//顶点着色器
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &vShaderSource, NULL); 
	glCompileShader(vertexShader);

	//片元着色器
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
	glCompileShader(fragmentShader);


	//着色器程序
	shaderProgram = glCreateProgram();

	//链接着色器
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//链接检查
	GLint success;
	char infolog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cerr << "Shader program linking failed. " << infolog << std::endl;
	}

	//删除着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

const GLchar* Shader::ReadShader(const char* filename)
{
	FILE* infile = NULL;
	fopen_s(&infile, filename, "rb");
	if (!infile) {
		std::cerr << "Unable to open file '" << filename << "'" << std::endl;
		return NULL;
	}
	fseek(infile, 0, SEEK_END);
	size_t len = ftell(infile);
	fseek(infile, 0, SEEK_SET);
	GLchar* source = new GLchar[len + 1];
	fread(source, 1, len, infile);
	fclose(infile);
	source[len] = '\0';
	return const_cast<const GLchar*>(source);
}

void Shader::setUniformFloat(const GLchar* loc, float value) const {
	glUniform1f(glGetUniformLocation(shaderProgram, loc), value);
}

void Shader::setUniformMatrix(const GLchar* loc, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, loc), 1, GL_FALSE, glm::value_ptr(value));
}
