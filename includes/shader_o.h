#ifndef SHADER_H
#define SHADER_H

// 链接静态库，必需先定义GLEW_STATIC 
#define GLEW_STATIC

#include <GL/glew.h>  
#include <GL/freeglut.h>  
#include <GLFW/glfw3.h>

class Shader
{
public:
	// 读着色器文件
	const GLchar* ReadShader(const char* filename);
	// 构造函数
	Shader(const GLchar* vSourcePath, const GLchar* fSourcePath_1, const GLchar* fSourcePath_2);
	// 使用着色器程序
	void use(GLuint f) {
		if (f == 1)
			glUseProgram(shaderProgramId[0]);
		else if (f == 2)
			glUseProgram(shaderProgramId[1]);
	}

private:
	// 着色器对象id
	GLuint shaderProgramId[2];
};
#endif

