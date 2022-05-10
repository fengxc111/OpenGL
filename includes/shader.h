#ifndef SHADER_H
#define SHADER_H

// ���Ӿ�̬�⣬�����ȶ���GLEW_STATIC 
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
	// ����ɫ���ļ�
	const GLchar* ReadShader(const char* filename);
	// ���캯��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// ʹ����ɫ������
	void use() {
		glUseProgram(shaderProgram);
	}
	void setUniformFloat(const GLchar* loc, float value) const;
	void setUniformMatrix(const GLchar* loc, glm::mat4 value) const;
	GLint getshaderProgramId(){
		return shaderProgram;
	}
private:
	// ��ɫ������id
	GLuint shaderProgram;
};
#endif

