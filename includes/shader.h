#ifndef SHADER_H
#define SHADER_H

// 链接静态库，必需先定义GLEW_STATIC 
#define GLEW_STATIC
#include <GL/glew.h>  
#include <GL/freeglut.h>  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader
{
public:
	// 读着色器文件
	const GLchar* ReadShader(const char* filename);
	// 构造函数
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// 使用着色器程序
	void use() {
		glUseProgram(shaderProgram);
	}
	void setUniformFloat(const GLchar* loc, float value) const;
	void setUniformMatrix(const GLchar* loc, glm::mat4 value) const;
	GLint getshaderProgramId(){
		return shaderProgram;
	}
private:
	// 着色器对象id
	GLuint shaderProgram;
};
#endif

